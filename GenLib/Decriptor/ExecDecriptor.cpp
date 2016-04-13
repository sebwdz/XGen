
#include        <boost/lexical_cast.hpp>
#include        "Cell/Brain.hpp"
#include        "Decriptor/Opt.hpp"
#include        "Decriptor/DecriptorManager.hpp"

void        Decriptor::exec()
{
  Monitor::get_instance()->begin_time(MN_INSTR);
  turn(m_block.get());
  Monitor::get_instance()->end_time(MN_INSTR);
  if (!m_attach)
    {
      SignalManager::catch_signals();
      make_move_line();
    }
}

GeneticalNode     *Decriptor::get_next_node(GeneticalNode *obj)
{
  return (obj);
}

SMART(GeneticalNode)        Decriptor::turn(GeneticalNode *node)
{
  SMART(GeneticalNode)             (Decriptor::*fct)(GeneticalNode*);
  SMART(GeneticalNode)             res;

  if (m_return)
      return (m_return);
  if (node->get_type() == INSTRU)
    {
      if (!node->get_function())
        {
          fct = DecriptorManager::get_instance()->get_function(node);
          node->set_function(fct);
        }
      else
        fct = node->get_function();
      res = (this->*(fct))(node);
    }
  else if (node->get_type() == VALUE)
  {
    res = nothing(node);
  }
  else if (node->get_type() == BLOCK)
      res = nothing(node);
  else
      res = get_chan(node);
  m_last = res;
  Monitor::get_instance()->add_val(MN_INSTR);
  return (res);
}

SMART(GeneticalNode)             Decriptor::nothing(GeneticalNode *node)
{
    SMART(GeneticalNode)        res;
    std::vector<SMART(GeneticalNode)>     &vct = node->get_son();

    for (unsigned int it = 0; it < vct.size(); it++)
    {
        turn(vct[it].get());
        if (m_return)
            return (m_return);
    }
  return (m_last);
}

SMART(GeneticalNode)         Decriptor::copy(GeneticalNode *node)
{
  std::vector<SMART(GeneticalNode)>    &vct = node->get_son();
  SMART(GeneticalNode)               cp;

  if (vct.size() > 1)
    {
      cp = get_chan(vct[0].get());
      copy_value(vct[1].get())->copy(cp);
    }
  return (cp);
}

SMART(GeneticalNode)        Decriptor::set_function(GeneticalNode *node)
{
  nodeValue                           value1;
  float                               value2;
  unsigned int                        it;
  std::vector<SMART(GeneticalNode)>   &vct = node->get_son();
  SMART(GeneticalNode)                res;

  it = 0;
  value2 = 0;
  value1._f = 0;
  if (vct.size() && node->get_value()._uc == SET)
  {
      res = get_chan(vct[it++].get());
      value1 = res->get_value();
  }
  for (it = it; it < vct.size(); it++)
    {
      value2 = get_value(get_next_node(vct[it].get()));
      if (node->get_value()._uc == SET)
      {
        res->get_value()._f = value2;
        return (res);
      }
      else if (it == 0)
          value1._f = value2;
      else if (node->get_value()._uc == ADD)
        value1._f += value2;
      else if (node->get_value()._uc == MULT)
        value1._f *= value2;
      else if (node->get_value()._uc == DIV || node->get_value()._uc == MOD)
        {
          if (value2 != 0)
            {
              if (node->get_value()._uc == DIV)
                value1._f /= value2;
              else
                value1._f = fmod(value1._f, value2);
            }
          else
            value1._f = 0;
        }
      else
        value1._f -= value2;
    }
  res = SMART(GeneticalNode)(new GeneticalNode);
  res->set_type(VALUE);
  res->set_value(value1);
  return (res);
}

int          Decriptor::comparator(GeneticalNode *node, GeneticalNode *content)
{
  unsigned int                    it;
  float                           value1;
  float                           value2;
  std::vector<SMART(GeneticalNode)>    &vct = content->get_son();
  SMART(GeneticalNode)          tmp;

  value2 = 0;
  value1 = 0;
  it = 0;
  if (node->get_type() == INSTRU && vct.size() > 0 &&
      (node->get_value()._uc == OR || node->get_value()._uc == AND || node->get_value()._uc == XOR))
    {
      for (it = 0; it < vct.size(); it++)
        {
          comp_funcion(vct[it].get());
          if (m_lastComp)
              value1 = 1;
          else
              value1 = 0;
          if (value2 && value1 && node->get_value()._uc == XOR)
            return (0);
          if (node->get_value()._uc == AND && !value1)
            return (0);
          if (!value2 && value1)
            value2 = value1;
        }
      if (!it && value1)
        return (1);
      if (!value2 && !value1 && (node->get_value()._uc == OR || node->get_value()._uc == XOR))
        return (0);
    }
  else if (node->get_value()._uc == NO && vct.size() > 0)
  {
      comp_funcion(vct[it].get());
        return (m_lastComp ? 0 : 1);
  }
  else if (vct.size() > 1)
    {
      value1 = get_value(get_next_node(vct[it++].get()));
      value2 = get_value(get_next_node(vct[it].get()));
      if (node->get_value()._uc == SUP && value1 <= value2)
        return (0);
      else if (node->get_value()._uc == INF && value1 >= value2)
        return (0);
      else if (node->get_value()._uc == EGAL && value1 != value2)
        return (0);
    }
  else
    return (0);
  return (1);
}

SMART(GeneticalNode)         Decriptor::comp_funcion(GeneticalNode *node)
{
  std::vector<SMART(GeneticalNode)>    &vct = node->get_son();
  GeneticalNode                   *content;

  if (vct.size() > 0)
    {
      content = get_next_node(vct[0].get());
      if (comparator(node, content))
        {
          m_lastComp = true;
          if (vct.size() > 1)
            turn(get_next_node(vct[1].get()));
            return (m_last);
        }
      else
        {
          m_lastComp = false;
          if (vct.size() > 2)
            turn(get_next_node(vct[2].get()));
        }
    }
  return (m_last);
}

SMART(GeneticalNode)          Decriptor::loop(GeneticalNode *node)
{
  std::vector<SMART(GeneticalNode)>    &vct = node->get_son();
  GeneticalNode                   *comp;
  GeneticalNode                   *code;

  if (vct.size() > 1)
    {
      comp = vct[0].get();
      code = vct[1].get();
      comp_funcion(comp);
      while (m_lastComp)
        {
          turn(code);
          if (m_return)
            return (SMART(GeneticalNode)());
          comp_funcion(comp);
        }
    }
  return (m_last);
}

SMART(GeneticalNode)          Decriptor::creat_function(GeneticalNode *node)
{
  std::vector<SMART(GeneticalNode)>        &vct = node->get_son();

  if (vct.size())
    get_line()->add_signal(node->get_value()._uc, new SMART(GeneticalNode)(copy_value(vct[0].get())));
  else if(node->get_value()._uc == DUPLIC)
      get_line()->add_signal(node->get_value()._uc, new SMART(GeneticalNode)(new GeneticalNode()));
  return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)          Decriptor::use_function(GeneticalNode *node)
{
  int     it;
  bool    use;
  std::vector<SMART(GeneticalNode)>        &vct = node->get_son();

  use = false;
  if (node->get_value()._uc == USE || node->get_value()._uc == SHARED)
    use = true;
  for (it = 0; it < (int)vct.size(); it++)
    {
      if (use)
        get_line()->get_shared()->set_ass(boost::static_pointer_cast<GeneticObj>(vct[it])->get_value()._ui,
                                        boost::static_pointer_cast<GeneticalNode>(get_line()->get_chan()->get_ass(boost::static_pointer_cast<GeneticObj>(vct[it])->get_value()._ui)));
      else
        get_line()->get_shared()->remove_ass(boost::static_pointer_cast<GeneticObj>(vct[it])->get_value()._ui);
    }
  return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)          Decriptor::decript_function(GeneticalNode *node)
{
  if ((node->get_value()._uc == KILL|| node->get_value()._uc == TAKEOUT) && m_parent)
    {
      if (m_attach)
        m_parent->get_parent()->get_line()->add_signal(node->get_value()._uc, m_parent);
      else
          m_parent->get_line()->add_signal(node->get_value()._uc, this);
    }
  else
    get_line()->add_signal(node->get_value()._uc, this);
  return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)              Decriptor::echo(GeneticalNode *node)
{
  unsigned int                      it;
  std::vector<SMART(GeneticalNode)> &vct = node->get_son();
  GeneticalNode                     *son;
  SMART(GeneticalNode)              ch;

  for (it = 0; it < vct.size(); it++)
    {
      son = vct[it].get();
      if (son->get_type() == VALUE && son->get_son().size())
      {
          if (son->get_value()._f == 0)
              echo(son);
          else
          {
            for (unsigned int i = 0; i < son->get_son().size(); i++)
            {
                if (son->get_value()._f == 1)
                    std::cout << get_value(son->get_son()[i].get());
                else
                    std::cout << (char)son->get_son()[i]->get_value()._f;
            }
          }

      }
      else
      {
        if (son->get_type() == GLOBAL_CHAN || son->get_type() == LOCAL_CHAN ||
              son->get_type() == FAST_CHAN || son->get_type() == INTERACTION || son->get_type() == INSTRU)
            {
                ch = get_chan(son);
                if (ch->get_son().size())
                {
                    for (unsigned int i = 0; i < ch->get_son().size(); i++)
                    {
                        if (ch->get_value()._f == 1)
                            std::cout << get_value(ch->get_son()[i].get());
                        else
                            std::cout << (char)ch->get_son()[i]->get_value()._f;
                    }
                }
                else
                    std::cout << get_value(son);
            }
        else
            std::cout << (char)son->get_value()._f;
      }
    }
  return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)              Decriptor::copy_value(GeneticalNode *node)
{
    SMART(GeneticalNode)          av;
    SMART(GeneticalNode)          res;
    std::vector<SMART(GeneticalNode)> &vct = node->get_son();
    GeneticalNode               *son;

    av = SMART(GeneticalNode)(new GeneticalNode());
    if (node->get_type() == VALUE || node->get_type() == EMPTY_CHAN)
    {
        av->set_type(node->get_type());
        av->set_value(node->get_value());
        for (unsigned int it = 0; it < vct.size(); it++)
        {
            son = vct[it].get();
            if (son->get_type() == GLOBAL_CHAN ||
                    son->get_type() == LOCAL_CHAN || son->get_type() == FAST_CHAN || son->get_type() == INSTRU)
                res = get_chan(son)->copy();
            else if (son->get_son().size() && son->get_type() == VALUE)
                res = copy_value(son);
            else
                res = son->copy();
            res->set_key(son->get_key());
            av->add_son(res);
        }
    }
    else if (node->get_type() != BLOCK)
        get_chan(node)->copy(av);
    else
        node->copy(av);
    return (av);
}

SMART(GeneticalNode)              Decriptor::call(GeneticalNode* node)
{
    GeneticalNode               *son;
    std::vector<SMART(GeneticalNode)> &vct = node->get_son();
    SMART(GeneticalNode)          res;

    if (vct.size() > 0)
    {
        if (vct.size() > 1)
            m_fast->get_ass()[Chanel::hash("__av__")] = copy_value(vct[1].get());
        son = vct[0].get();
        if (son->get_type() == GLOBAL_CHAN ||
                son->get_type() == LOCAL_CHAN ||
                son->get_type() == FAST_CHAN || son->get_type() == INSTRU)
            turn(get_chan(son).get());
        else
            turn(son);
        res = m_return;
        if (!res)
            res = m_last;
        m_return = SMART(GeneticalNode)();
    }
    return (res);
}

SMART(GeneticalNode)            Decriptor::ref_function(GeneticalNode *node)
{
    std::vector<SMART(GeneticalNode)>   &vct = node->get_son();
    SMART(GeneticalNode)                res;
    void                                *ptr;

    if (vct.size())
    {
        if (node->get_value()._uc == DEREF)
        {
            if (!(res = boost::static_pointer_cast<GeneticalNode>(get_chan(vct[0].get())->get_ref())))
                return (SMART(GeneticalNode)(new GeneticalNode()));
            return (getSubChan(res, vct, 1));
        }
        else
        {
            res = SMART(GeneticalNode)(new GeneticalNode());
            if (vct[0]->get_type() != VALUE && vct[0]->get_type() != BLOCK)
                res->set_ref(get_chan(vct[0].get()));
            else
                res->set_ref(copy_value(vct[0].get()));
            ptr = res->get_ref().get();
            res->get_value()._ptr = ptr;
            return (res);
        }
    }
    return (SMART(GeneticalNode)(new GeneticalNode()));
}

SMART(GeneticalNode)            Decriptor::node_size(GeneticalNode *node)
{
    SMART(GeneticalNode)        res(new GeneticalNode);
    std::vector<SMART(GeneticalNode)>   &vct = node->get_son();

    if (vct.size())
        res->get_value()._f = get_chan(vct[0].get())->get_son().size();
    return (res);
}

SMART(GeneticalNode)            Decriptor::ret(GeneticalNode *node)
{
    if (node->get_son().size())
    {
        if (node->get_son()[0]->get_type() != VALUE)
            m_return = get_chan(node->get_son()[0].get());
        else
            m_return = node->get_son()[0];
    }
    return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)            Decriptor::pow(GeneticalNode *node)
{
    SMART(GeneticalNode)        res(new GeneticalNode);
    std::vector<SMART(GeneticalNode)>   &vct = node->get_son();

    if (vct.size() < 2)
        return (res);
    res->get_value()._f = std::pow(get_value(vct[0].get()), get_value(vct[1].get()));
    return (res);
}

SMART(GeneticalNode)            Decriptor::rand(GeneticalNode *node)
{
    SMART(GeneticalNode)        res(new GeneticalNode);

    (void)node;
    res->get_value()._f = random();
    return (res);
}

SMART(GeneticalNode)            Decriptor::erase(GeneticalNode *node)
{
    std::vector<SMART(GeneticalNode)>   &vct = node->get_son();
    SMART(GeneticalNode)                chan;
    SMART(GeneticalNode)                chan2;
    nodeValue                           it;
    boost::unordered_map<unsigned int, SMART(GeneticalNode)>::iterator  i;

    if (vct.size() > 1 && (chan = get_chan(vct[0].get()))->get_son().size())
    {
        if (vct[1]->get_type() != VALUE && vct[1]->get_type() != EMPTY_CHAN)
            it = (chan2 = get_chan(vct[1].get()))->get_value();
        else
            it = (chan2 = vct[1])->get_value();
        if (chan2->get_type() == VALUE && it._f < chan->get_son().size())
        {
            for (i = chan->get_ass().begin(); i != chan->get_ass().end(); i++)
            {
                if (i->second == chan->get_son()[it._f])
                {
                    chan->get_ass().erase(i);
                    break;
                }
                chan->get_son().erase(chan->get_son().begin() + (unsigned int)it._f);
            }
        }
        else
        {
            for (unsigned int ix = 0; ix < chan->get_son().size(); ix++)
            {
                if (chan->get_son_ref(ix) == chan->get_ass(it._ui))
                {
                    chan->get_son().erase(chan->get_son().begin() + ix);
                    break;
                }
            }
            chan->get_ass().erase(it._ui);
        }
    }
    return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)            Decriptor::move_pos(GeneticalNode *node)
{
    std::pair<float, float>     vct;

    vct.first = get_line()->get_chan()->get_ass(Chanel::hash("__pos__"))->get_son_ref(0)->get_value()._f - m_parent->get_pos().first;
    vct.second = get_line()->get_chan()->get_ass(Chanel::hash("__pos__"))->get_son_ref(1)->get_value()._f - m_parent->get_pos().second;
    (void)node;
    if (!m_attach)
    {
        m_pos.first = m_line.get_chan()->get_ass(Chanel::hash("__pos__"))->get_son_ref(0)->get_value()._f;
        m_pos.second = m_line.get_chan()->get_ass(Chanel::hash("__pos__"))->get_son_ref(1)->get_value()._f;
        CAST(ModuleClass*)(m_parent)->move_object(this);
    }
    else
    {
        m_parent->get_pos().first = get_line()->get_chan()->get_ass(Chanel::hash("__pos__"))->get_son_ref(0)->get_value()._f;
        m_parent->get_pos().second = get_line()->get_chan()->get_ass(Chanel::hash("__pos__"))->get_son_ref(1)->get_value()._f;
        CAST(ModuleClass*)(m_parent)->change_pos(vct);
        CAST(ModuleClass*)(m_parent->get_parent())->move_object(m_parent);
    }
    return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)            Decriptor::round(GeneticalNode *node)
{
    SMART(GeneticalNode)        res(new GeneticalNode);
    double                      p;
    double                      tmp;

    if (node->get_son().size() > 1)
    {
        p = std::pow(10, get_value(node->get_son()[1].get()));
        tmp = p * get_value(node->get_son()[0].get());
        tmp = (int)(tmp + 0.0001);
        tmp /= p;
        res->get_value()._f = tmp;
    }
    return (res);
}

SMART(GeneticalNode)            Decriptor::sqrt(GeneticalNode *node)
{
    SMART(GeneticalNode)        res;
    if (node->get_son().size())
    {
        res = SMART(GeneticalNode)(new GeneticalNode);
        res->get_value()._f = std::sqrt(get_value(node->get_son()[0].get()));
    }
    return (res);
}

SMART(GeneticalNode)            Decriptor::key_exist(GeneticalNode *node)
{
    std::vector<SMART(GeneticalNode)>   &vct = node->get_son();
    SMART(GeneticalNode)                chan;
    SMART(GeneticalNode)                res(new GeneticalNode());
    GeneticalNode                       *use;

    if (vct.size() > 1)
    {
        chan = get_chan(vct[0].get());
        use = vct[1].get();
        if (use->get_type() != EMPTY_CHAN && use->get_type() != VALUE)
            use = get_chan(use).get();
        if (use->get_type() == EMPTY_CHAN && chan->get_ass(use->get_value()._ui, false))
            res->get_value()._f = 1;
        else if (use->get_type() == VALUE && chan->get_son_ref(use->get_value()._f, false))
            res->get_value()._f = 1;
    }
    return (res);
}

SMART(GeneticalNode)            Decriptor::attach(GeneticalNode *node)
{
    std::vector<SMART(GeneticalNode)>   &vct = node->get_son();
    GeneticalNode                       *use;
    Decriptor                           *decriptor;

    if (vct.size() > 0)
    {
        if (vct[0]->get_type() == VALUE)
            use = vct[0].get();
        else
            use = get_chan(vct[0].get()).get();
        for (unsigned int it = 0; it < use->get_son().size(); it++)
        {
            decriptor = new Decriptor(NULL);
            decriptor->set_block(use->get_son_ref(it)->copy());
            decriptor->catch_simple(ATTACH, m_parent);
        }
    }
    return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)        Decriptor::free(GeneticalNode* node)
{
    (void)node;
    if (m_parent)
        CAST(ModuleClass*)(m_parent)->add_signal(FREE, this);
    return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)        Decriptor::incr(GeneticalNode* node)
{
    std::vector<SMART(GeneticalNode)>   &vct = node->get_son();
    SMART(GeneticalNode)                chan;
    float                   value;

    if (vct.size() > 0)
    {
        chan = get_chan(vct[0].get());
        if (vct.size() > 1)
            value = get_value(vct[1].get());
        else
            value = 1;
        if (node->get_value()._uc == INCR)
            chan->get_value()._f += value;
        else
            chan->get_value()._f -= value;
    }
    return (chan);
}

SMART(GeneticalNode)    Decriptor::val(GeneticalNode* node)
{
    std::vector<SMART(GeneticalNode)>   &vct = node->get_son();

    if (vct.size())
        return (vct[0]);
    return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)    Decriptor::copy_one(GeneticalNode *node)
{
    std::vector<SMART(GeneticalNode)>   &vct = node->get_son();
    SMART(GeneticalNode)                chan;
    SMART(GeneticalNode)                chan2;

    if (vct.size() > 1)
    {
        chan = get_chan(vct[0].get());
        chan2 = get_chan(vct[1].get());
        chan->set_type(chan2->get_type());
        chan->set_value(chan2->get_value());
        chan->set_ref(chan2->get_ref());
        chan->set_function(NULL);
        return (chan);
    }
    return (SMART(GeneticalNode)());
}
