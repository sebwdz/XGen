
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

  if (m_return)
      return (SMART(GeneticalNode)());
  if (node->get_type() == INSTRU)
    {
      if (!node->get_function())
        {
          fct = DecriptorManager::get_instance()->get_function(node);
          node->set_function(fct);
        }
      else
        fct = node->get_function();
    }
  else
    fct = &Decriptor::nothing;
  Monitor::get_instance()->add_val(MN_INSTR);
  return ((this->*(fct))(node));
}

SMART(GeneticalNode)             Decriptor::nothing(GeneticalNode *node)
{
    SMART(GeneticalNode)        res;

  std::vector<SMART(GeneticalNode)>     &vct = node->get_son();

    for (int it = 0; it < (int)vct.size(); it++)
    {
        turn(get_next_node(vct[it].get()));
        if (m_return)
            return (res);
    }
  return (res);
}

SMART(GeneticalNode)         Decriptor::copy(GeneticalNode *node)
{
  std::vector<SMART(GeneticalNode)>    &vct = node->get_son();
  SMART(GeneticalNode)               cp;

  if (vct.size() > 1)
    {
      cp = get_chan(vct[0].get());
      if (vct[1]->get_type() == GLOBAL_CHAN ||
              vct[1]->get_type() == FAST_CHAN ||
              vct[1]->get_type() == LOCAL_CHAN ||
              vct[1]->get_type() == INSTRU)
      {
        get_chan(vct[1].get())->copy(cp);
      }
      else
        vct[1]->copy(cp);
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
      res = get_chan(get_next_node(vct[it].get()));
      value1 = res->get_value();
  }
  else if (vct.size())
      value1._f = get_value(get_next_node(vct[it].get()));
  for (it = 1; it < vct.size(); it++)
    {
      value2 = get_value(get_next_node(vct[it].get()));
      if (node->get_value()._uc == SET)
      {
        value1._f = value2;
        res->get_value() = value1;
        return (res);
      }
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
          if ((tmp = comp_funcion(get_next_node(vct[it].get()))))
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
    return (comp_funcion(get_next_node(vct[it].get())) ? 0 : 1);
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
          if (vct.size() > 1)
            turn(get_next_node(vct[1].get()));
            return (SMART(GeneticalNode)(new GeneticalNode()));
        }
      else
        {
          if (vct.size() > 2)
            turn(get_next_node(vct[2].get()));
        }
    }
  return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)          Decriptor::loop(GeneticalNode *node)
{
  std::vector<SMART(GeneticalNode)>    &vct = node->get_son();
  GeneticalNode                   *comp;
  GeneticalNode                   *code;

  if (vct.size() > 1)
    {
      comp = get_next_node(vct[0].get());
      code = get_next_node(vct[1].get());
      while (comp_funcion(comp)) {
          turn(code);
          if (m_return)
            return (SMART(GeneticalNode)());
        }
    }
  return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)          Decriptor::creat_function(GeneticalNode *node)
{
  std::vector<SMART(GeneticalNode)>        &vct = node->get_son();

  if (vct.size())
    get_line()->add_signal(node->get_value()._uc, new SMART(GeneticalNode)(copy_value(vct[0].get())));
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

  for (it = 0; it < vct.size(); it++)
    {
      son = vct[it].get();
      if (son->get_type() == GLOBAL_CHAN || son->get_type() == LOCAL_CHAN ||
          son->get_type() == FAST_CHAN || son->get_type() == INTERACTION || son->get_type() == INSTRU)
        {
          std::cout << get_value(son);
        }
      else
        std::cout << (char)son->get_value()._f;
    }
  return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)              Decriptor::copy_value(GeneticalNode *node)
{
    SMART(GeneticalNode)          av;
    std::vector<SMART(GeneticalNode)> &vct = node->get_son();
    GeneticalNode               *son;

    av = SMART(GeneticalNode)(new GeneticalNode());
    if (node->get_type() == VALUE)
    {
        for (unsigned int it = 0; it < vct.size(); it++)
        {
            son = vct[it].get();
            if (son->get_type() == GLOBAL_CHAN ||
                    son->get_type() == LOCAL_CHAN || son->get_type() == FAST_CHAN || son->get_type() == INSTRU)
                av->add_son(get_chan(son)->copy());
            else if (son->get_son().size() && son->get_type() == VALUE)
                av->add_son(copy_value(son));
            else
                av->add_son(son->copy());
        }
    }
    else
        get_chan(node)->copy(av);
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
        m_return = SMART(GeneticalNode)();
    }
    return (res);
}

SMART(GeneticalNode)            Decriptor::ref_function(GeneticalNode *node)
{
    std::vector<SMART(GeneticalNode)>   &vct = node->get_son();
    SMART(GeneticalNode)                res;

    if (vct.size())
    {
        if (node->get_value()._uc == DEREF)
        {
            if (!(res = boost::static_pointer_cast<GeneticalNode>(get_chan(vct[0].get())->get_ref())))
                res = vct[0];
            return (getSubChan(res, vct, 1));
        }
        else
        {
            res = SMART(GeneticalNode)(new GeneticalNode());
            res->set_ref(get_chan(vct[0].get()));
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
    float                               it;

    if (vct.size() > 2 && (chan = get_chan(vct[0].get()))->get_son().size())
    {
        it = get_value(vct[1].get());
        if (it < chan->get_son().size())
        {
            chan->get_son().erase(chan->get_son().begin() + (int)it);
        }
    }
    return (SMART(GeneticalNode)());
}

SMART(GeneticalNode)            Decriptor::move_pos(GeneticalNode *node)
{
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
        CAST(ModuleClass*)(m_parent->get_parent())->move_object(m_parent);
    }
    return (SMART(GeneticalNode)());
}
