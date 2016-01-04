
#include        "Cell/Brain.hpp"
#include        "Decriptor/Decriptor.hpp"

Decriptor::Decriptor(Object *obj) : Movable(obj)
{
  m_jmp = 0;
  m_type ^= TYPE_DECRIPTOR;
  m_sig.insert(std::make_pair(ATTACH, (SIG_CATCH)(&Decriptor::catch_simple)));
  m_attach = false;
  m_fast = SMART(GeneticalNode)(new GeneticalNode());
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

void        Decriptor::set_block(SMART(GeneticalNode) block)
{
  m_block = block;
}

void        Decriptor::set_attach(bool attach)
{
  m_attach = attach;
  reset(m_block);
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
  if (node->get_type() != VALUE)
      return (get_chan(node)->get_value()._f);
  return (node->get_value()._f);
}

SMART(GeneticalNode)    Decriptor::get_chan(GeneticalNode *node)
{
  unsigned int                        it;
  unsigned int                        var;
  SMART(GeneticalNode)                chan;
  GeneticalNode                       *tmp;
  std::vector<SMART(GeneticalNode)>   &vct = node->get_son();

  if (node->get_chan())
    return (node->get_chan());
  if (node->get_type() == FAST_CHAN)
    chan = m_fast;
  else if (node->get_type() == LOCAL_CHAN && node->get_block())
    chan = node->get_block()->get_local();
  else if (node->get_type() == INTERACTION)
    chan = get_line()->get_interaction();
  else
    chan = get_line()->get_chan();
  var = 0;
  for (it = 0; it < vct.size(); it++) {
      if (vct[it]->get_type() == EMPTY_CHAN)
        chan = chan->get_ass(vct[it]->get_value()._ui);
      else if (vct[it]->get_type() == VALUE)
        chan = chan->get_son_ref((unsigned int)vct[it]->get_value()._f);
      else
        {
          var = 1;
          tmp = get_chan(vct[it].get()).get();
          if (tmp->get_type() == VALUE)
            chan = chan->get_son_ref((unsigned int)tmp->get_value()._f);
          else
            chan = chan->get_ass(tmp->get_value()._ui);
        }
    }
  if (var)
      return (chan);
  node->set_chan(chan);
  return (node->get_chan());
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
      parent = static_cast<ModuleClass*>(sig);
      CAST(ModuleClass*)(m_parent)->get_map()->remove_object(this);
      parent->attach_decriptor(this);
    }
}

void        Decriptor::catch_duplic(unsigned int code, void *sig)
{
  (void)code;
  (void)sig;
}
