
#include        "Cell/Brain.hpp"
#include        "Decriptor/Decriptor.hpp"

Decriptor::Decriptor(Object *obj) : Movable(obj)
{
  m_jmp = 0;
  m_type ^= TYPE_DECRIPTOR;
  m_sig.insert(std::make_pair(ATTACH, (SIG_CATCH)(&Decriptor::catch_simple)));
  m_attach = false;
  m_fast = SMART(GeneticalNode)(new GeneticalNode());
  m_lastComp = false;
}

Decriptor::~Decriptor()
{
}

LineDecript     *Decriptor::get_line()
{
  if (m_attach && m_parent)
    return (m_parent->get_line());
  return (&m_line);
}

SMART(GeneticalNode)    Decriptor::get_fast() const
{
    return (m_fast);
}

void                    Decriptor::set_return(SMART(GeneticalNode) node)
{
    m_return = node;
}

void        Decriptor::set_block(SMART(GeneticalNode) block)
{
  m_block = block;
}

void        Decriptor::set_attach(bool attach)
{
  m_attach = attach;
  if (m_block)
    reset(m_block);
}

bool        Decriptor::get_attach()
{
    return (m_attach);
}

void        Decriptor::reset(SMART(GeneticalNode) obj)
{
  std::vector<SMART(GeneticalNode)>  son = obj->get_son();

  static_cast<GeneticalNode*>(obj.get())->set_chan(SMART(GeneticalNode)());
  for (unsigned int it = 0; it < son.size(); it++)
    reset(son[it]);
}

SMART(GeneticalNode)     Decriptor::get_block() const
{
  return (m_block);
}

float    Decriptor::get_value(GeneticalNode *node)
{
  if (node->get_type() != VALUE && node->get_type() != EMPTY_CHAN)
      return (get_chan(node)->get_value()._f);
  return (node->get_value()._f);
}

SMART(GeneticalNode)    Decriptor::get_chan(GeneticalNode *node)
{
  SMART(GeneticalNode)                chan;
  std::vector<SMART(GeneticalNode)>   &vct = node->get_son();

  /*if (node->get_chan())
    return (node->get_chan());*/
  if (node->get_type() == FAST_CHAN)
    chan = m_fast;
  else if (node->get_type() == LOCAL_CHAN && node->get_block())
    chan = node->get_block()->get_local();
  else if (node->get_type() == INTERACTION)
    chan = get_line()->get_interaction();
  else if (node->get_type() == INSTRU)
  {
      chan = turn(node);
      if (!chan)
          chan = SMART(GeneticalNode)(new GeneticalNode);
      return (chan);
  }
  else
    chan = get_line()->get_chan();
  return (getSubChan(chan, vct, 0));
}

SMART(GeneticalNode)        Decriptor::getSubChan(SMART(GeneticalNode) chan, std::vector<SMART(GeneticalNode)> &vct, unsigned int i)
{
    GeneticalNode                       *tmp;
    SMART(GeneticalNode)                x;

    for (unsigned it = i; it < vct.size(); it++) {
        if (vct[it]->get_type() == EMPTY_CHAN)
          chan = chan->get_ass(vct[it]->get_value()._ui);
        else if (vct[it]->get_type() == VALUE)
        {
            if (vct[it]->get_value()._f >= 0)
                chan = chan->get_son_ref((unsigned int)vct[it]->get_value()._f);
        }
        else if (vct[it]->get_type() == INSTRU)
        {
            x = turn(vct[it].get());
            if (!x)
                x = SMART(GeneticalNode)(new GeneticalNode);
            if (x->get_value()._f >= 0)
            chan = chan->get_son_ref((unsigned int)x->get_value()._f);
        }
        else
          {
            tmp = get_chan(vct[it].get()).get();
            if (tmp->get_type() == VALUE)
            {
                if (tmp->get_value()._f >= 0)
                    chan = chan->get_son_ref((unsigned int)tmp->get_value()._f);
            }
            else
              chan = chan->get_ass(tmp->get_value()._ui);
          }
      }
    return (chan);
}

void        Decriptor::catch_signals()
{
  SignalManager::catch_signals();
}

void        Decriptor::catch_simple(unsigned int code, void *sig)
{
  ModuleClass     *parent;

  if (code == ATTACH && !m_attach)
    {
      parent = CAST(ModuleClass*)(sig);
      if (m_parent)
        CAST(ModuleClass*)(m_parent)->get_map()->remove_object(this);
      parent->attach_decriptor(this);
    }
}

void        Decriptor::catch_duplic(unsigned int code, void *sig)
{
  (void)code;
  (void)sig;
}

SMART(GeneticalNode)    Decriptor::get_return()
{
    return (m_return);
}
