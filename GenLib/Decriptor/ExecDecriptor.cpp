
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

void        Decriptor::turn(GeneticalNode *node)
{
  int             (Decriptor::*fct)(GeneticalNode*);

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
  (this->*(fct))(node);
}

int             Decriptor::nothing(GeneticalNode *node)
{
  int         it;
  std::vector<SMART(GeneticalNode)>    &vct = node->get_son();

  for (it = 0; it < (int)vct.size(); it++)
    turn(get_next_node(vct[it].get()));
  return (0);
}

int        Decriptor::copy(GeneticalNode *node)
{
  std::vector<SMART(GeneticalNode)>    &vct = node->get_son();
  SMART(GeneticalNode)               cp;

  if (vct.size() > 1)
    {
      cp = get_chan(vct[0].get());
      if (vct[1]->get_type() != VALUE)
        get_chan(vct[1].get())->copy(cp);
      else
        vct[1]->copy(cp);
    }
  return (0);
}

int        Decriptor::set_function(GeneticalNode *node)
{
  nodeValue                           value1;
  float                               value2;
  unsigned int                        it;
  GeneticalNode                        *tmp;
  std::vector<SMART(GeneticalNode)>   &vct = node->get_son();

  it = 0;
  value2 = 0;
  for (it = 0; it + 1 < vct.size(); it++)
    {
      tmp = get_chan(get_next_node(vct[it++].get())).get();
      value1 = tmp->get_value();
      value2 = get_value(get_next_node(vct[it].get()));
      if (node->get_value()._uc == SET)
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
      else if (value1._f > value2)
        value1._f -= value2;
      else
        value1._f = 0;
      tmp->set_value(value1);
    }
  return (0);
}

int         Decriptor::comparator(GeneticalNode *node, GeneticalNode *content)
{
  unsigned int                    it;
  float                           value1;
  float                           value2;
  std::vector<SMART(GeneticalNode)>    &vct = content->get_son();

  value2 = 0;
  value1 = 0;
  it = 0;
  if (node->get_type() == INSTRU && vct.size() > 0 &&
      (node->get_value()._uc == OR || node->get_value()._uc == AND || node->get_value()._uc == XOR))
    {
      for (it = 0; it < vct.size(); it++)
        {
          value1 = comp_funcion(get_next_node(vct[it].get()));
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

int        Decriptor::comp_funcion(GeneticalNode *node)
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
          return (1);
        }
      else
        {
          if (vct.size() > 2)
            turn(get_next_node(vct[2].get()));
        }
    }
  return (0);
}

int         Decriptor::loop(GeneticalNode *node)
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
        }
    }
  return (0);
}

int         Decriptor::creat_function(GeneticalNode *node)
{
  get_line()->add_signal(node->get_value()._uc, node);
  return (0);
}

int         Decriptor::use_function(GeneticalNode *node)
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
  return (0);
}

int         Decriptor::decript_function(GeneticalNode *node)
{
  if ((node->get_value()._uc == KILL|| node->get_value()._uc == TAKEOUT) && m_parent)
    {
      if (m_attach)
        m_parent->get_parent()->get_line()->add_signal(node->get_value()._uc, m_parent);
    }
  else
    get_line()->add_signal(node->get_value()._uc, this);
  return (0);
}

int     Decriptor::jmp_function(GeneticalNode *node)
{
  return (nothing(node));
}

int             Decriptor::echo(GeneticalNode *node)
{
  unsigned int                      it;
  std::vector<SMART(GeneticalNode)> &vct = node->get_son();
  GeneticalNode                     *son;

  for (it = 0; it < vct.size(); it++)
    {
      son = CAST(GeneticalNode*)(vct[it].get());
      if (son->get_type() == GLOBAL_CHAN || son->get_type() == LOCAL_CHAN ||
          son->get_type() == FAST_CHAN || son->get_type() == INTERACTION)
        {
          std::cout << get_value(son);
        }
      else
        std::cout << (char)son->get_value()._f;
    }
  return (0);
}
