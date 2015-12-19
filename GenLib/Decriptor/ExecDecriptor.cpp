
#include        "Cell/Brain.hpp"
#include        "Decriptor/Opt.hpp"
#include        "Decriptor/DecriptorManager.hpp"

void        Decriptor::exec()
{
  GeneticObj        *block;

  Monitor::get_instance()->begin_time(MN_INSTR);
  block = get_next_node(m_block.get());
  if (block)
    turn(CAST(GeneticalNode*)(block));
  Monitor::get_instance()->end_time(MN_INSTR);
  if (!m_attach)
    {
      SignalManager::catch_signals();
      make_move_line();
    }
}

GeneticalNode     *Decriptor::get_next_node(GeneticObj *obj)
{
  GeneticObj      *tmp;

  tmp = obj;
  if (!tmp->get_type() && CAST(GeneticBlock*)(obj)->get_next())
    return (CAST(GeneticBlock*)(obj)->get_next());
  while (obj && !obj->get_type())
    obj = CAST(GeneticBlock*)(obj)->get_obj().get();
  if (!obj)
    return (NULL);
  if (!tmp->get_type())
    CAST(GeneticBlock*)(tmp)->set_next(CAST(GeneticalNode*)(obj));
  return (CAST(GeneticalNode*)(obj));
}

void        Decriptor::turn(GeneticalNode *node)
{
  int             (Decriptor::*fct)(GeneticalNode*);

  if (!node)
    return ;
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
  std::vector<SMART(ObjClass)>    &vct = node->get_son();

  for (it = 0; it < (int)vct.size(); it++)
    turn(CAST(GeneticalNode*)(get_next_node(CAST(GeneticObj*)(vct[it].get()))));
  return (0);
}

int        Decriptor::set_function(GeneticalNode *node)
{
  float           value1;
  float           value2;
  unsigned int    it;
  Chanel          *tmp;
  std::vector<SMART(ObjClass)>    &vct = node->get_son();

  it = 0;
  value2 = 0;
  for (it = 0; it + 1 < vct.size(); it++)
    {
      tmp = get_chan(get_next_node(CAST(GeneticObj*)(vct[it++].get())));
      value1 = tmp->get_value();
      value2 = get_value(get_next_node(CAST(GeneticObj*)(vct[it].get())));
      if (node->get_value() == SET)
        value1 = value2;
      else if (node->get_value() == ADD)
        value1 += value2;
      else if (node->get_value() == MULT)
        value1 *= value2;
      else if (node->get_value() == DIV)
        {
          if (value2 != 0)
            value1 /= value2;
        }
      else if (value1 > value2)
        value1 -= value2;
      else
        value1 = 0;
      tmp->set_value(value1);
    }
  return (0);
}

int         Decriptor::comparator(GeneticalNode *node, GeneticalNode *content)
{
  unsigned int                    it;
  float                           value1;
  float                           value2;
  std::vector<SMART(ObjClass)>    &vct = content->get_son();

  value2 = 0;
  value1 = 0;
  it = 0;
  if (node->get_type() == INSTRU && vct.size() > 0 &&
      (node->get_value() == OR || node->get_value() == AND || node->get_value() == XOR))
    {
      for (it = 0; it < vct.size(); it++)
        {
          value1 = comp_funcion(get_next_node(CAST(GeneticObj*)(vct[it].get())));
          if (value2 && value1 && node->get_value() == XOR)
            return (0);
          if (node->get_value() == AND && !value1)
            return (0);
          if (!value2 && value1)
            value2 = value1;
        }
      if (!it && value1)
        return (1);
      if (!value2 && !value1 && (node->get_value() == OR || node->get_value() == XOR))
        return (0);
    }
  else if (node->get_value() == NO && vct.size() > 0)
    return (comp_funcion(get_next_node(CAST(GeneticObj*)(vct[it].get()))) ? 0 : 1);
  else if (vct.size() > 1)
    {
      value1 = get_value(get_next_node(CAST(GeneticObj*)(vct[it++].get())));
      value2 = get_value(get_next_node(CAST(GeneticObj*)(vct[it].get())));
      if (node->get_value() == SUP && value1 <= value2)
        return (0);
      else if (node->get_value() == INF && value1 >= value2)
        return (0);
      else if (node->get_value() == EGAL && value1 != value2)
        return (0);
    }
  else
    return (0);
  return (1);
}

int        Decriptor::comp_funcion(GeneticalNode *node)
{
  std::vector<SMART(ObjClass)>    &vct = node->get_son();
  GeneticalNode                   *content;

  if (vct.size() > 0)
    {
      content = get_next_node(CAST(GeneticObj*)(vct[0].get()));
      if (comparator(node, content))
        {
          if (vct.size() > 1)
            turn(get_next_node(CAST(GeneticObj*)(vct[1].get())));
          return (1);
        }
      else
        {
          if (vct.size() > 2)
            turn(get_next_node(CAST(GeneticObj*)(vct[2].get())));
          return (0);
        }
    }
  return (0);
}

int         Decriptor::creat_function(GeneticalNode *node)
{
  get_line()->add_signal(node->get_value(), node);
  return (0);
}

int         Decriptor::use_function(GeneticalNode *node)
{
  int     it;
  bool    use;
  bool    mode;
  std::vector<SMART(ObjClass)>        &vct = node->get_son();

  use = false;
  if (node->get_value() == USE || node->get_value() == SHARED)
    use = true;
  mode = true;
  if (node->get_value() == USE || node->get_value() == UNUSE)
    mode = false;
  for (it = 0; it < (int)vct.size(); it++)
    {
      if (!mode)
        get_chan(get_next_node(CAST(GeneticObj*)(vct[it].get())))->set_use(use);
      else
        get_chan(get_next_node(CAST(GeneticObj*)(vct[it].get())))->set_shared(use);
    }
  return (0);
}

int         Decriptor::decript_function(GeneticalNode *node)
{
  if ((node->get_value() == KILL|| node->get_value() == TAKEOUT) && m_parent)
    {
      if (m_attach)
        m_parent->get_parent()->get_line()->add_signal(node->get_value(), m_parent);
    }
  else
    get_line()->add_signal(node->get_value(), this);
  return (0);
}

int     Decriptor::jmp_function(GeneticalNode *node)
{
  return (nothing(node));
}

int             Decriptor::echo(GeneticalNode *node)
{
  unsigned int           it;
  std::vector<SMART(ObjClass)>    &vct = node->get_son();
  GeneticalNode                   *son;

  for (it = 0; it < vct.size(); it++)
    {
      son = CAST(GeneticalNode*)(vct[it].get());
      if (son->get_type() == GLOBAL_CHAN || son->get_type() == LOCAL_CHAN ||
          son->get_type() == FAST_CHAN)
        {
          std::cout << get_value(son);
        }
      else
        std::cout << (char)son->get_value();
    }
  return (0);
}

int             Decriptor::set_var_function(GeneticalNode *node)
{
  int              it;
  GeneticalNode   *cur;
  std::vector<SMART(ObjClass)>    &vct = node->get_son();

  for (it = 0; it < (int)vct.size(); it++)
    {
      Monitor::get_instance()->add_val(MN_INSTR);
      cur = get_next_node(CAST(GeneticObj*)(vct[it].get()));
      set_chan(cur);
    }
  return (0);
}

void        Decriptor::set_chan(GeneticalNode *node)
{
  GeneticalNode   *cp;
  ChanPropriety   *prop;
  int             it;
  std::vector<SMART(ObjClass)>    &vct = node->get_son();

  prop = get_line()->get_prop(node->get_value());
  for (it = 0; it < (int)vct.size(); it++)
    {
      Monitor::get_instance()->add_val(MN_INSTR);
      cp = get_next_node(CAST(GeneticObj*)(vct[it].get()));
      set_propriety(cp, prop);
    }
}

void        Decriptor::set_propriety(GeneticalNode *node, ChanPropriety *prop)
{
  unsigned int  it;
  GeneticalNode   *cp;
  std::vector<SMART(ObjClass)>    &vct = node->get_son();

  for (it = 0; it < vct.size(); it++)
    {
      Monitor::get_instance()->add_val(MN_INSTR);
      cp = get_next_node(CAST(GeneticObj*)(vct[it].get()));
      if (node->get_value() == TYPE)
        prop->set_type(cp->get_value());
      else if (node->get_value() == DST || node->get_value() == PW || node->get_value() == MINDST) {
          prop->set_pow(node->get_value(), get_value(cp));
        }
      else if (node->get_value() == ACT)
        {
          if (it == 0)
            {
              prop->set_chan(get_line()->get_chan(cp->get_value()));
              prop->set_act(TO, cp->get_value());
            }
          else
            prop->set_act(OTH, cp->get_value());
        }
    }
}
