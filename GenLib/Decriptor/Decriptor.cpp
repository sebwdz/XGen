
#include        "Cell/Brain.hpp"
#include        "Decriptor/Decriptor.hpp"

Decriptor::Decriptor(Object *obj) : Movable(obj)
{
  m_jmp = 0;
  m_type ^= TYPE_DECRIPTOR;
  m_sig.insert(std::make_pair(ATTACH, (SIG_CATCH)(&Decriptor::catch_simple)));
  m_attach = false;
}

Decriptor::~Decriptor()
{
  for (USE_LIST::iterator it = m_fast.begin(); it != m_fast.end(); it++)
    delete it->second;
}

LineDecript     *Decriptor::get_line()
{
  if (m_attach && m_parent)
    return (m_parent->get_line());
  return (&m_line);
}

void        Decriptor::set_block(SMART(GeneticObj) block)
{
  m_block = block;
}

void        Decriptor::set_attach(bool attach)
{
  m_attach = attach;
  reset(m_block);
}

void        Decriptor::reset(SMART(GeneticObj) obj)
{
  std::vector<SMART(ObjClass)>  son = obj->get_son();

  if (obj->get_type() != BLOCK)
    {
      static_cast<GeneticalNode*>(obj.get())->set_chan(NULL);
      for (unsigned int it = 0; it < son.size(); it++)
        reset(boost::static_pointer_cast<GeneticObj>(son[it]));
    }
  else
    reset(CAST(GeneticBlock*)(obj.get())->get_obj());
}

SMART(GeneticObj)     Decriptor::get_block() const
{
  return (m_block);
}

float    Decriptor::get_value(GeneticalNode *node)
{
  if (node->get_type() != VALUE)
    return (get_chan(node)->get_value());
  return (node->get_value()._f);
}

Chanel*         Decriptor::get_chan(GeneticalNode *node)
{
  USE_LIST::iterator  it;
  Chanel              *chan;

  if (node->get_chan())
    return (node->get_chan());
  if (node->get_type() == FAST_CHAN) {
      if ((it = m_fast.find(node->get_value()._ui)) == m_fast.end())
        {
          chan = new Chanel();
          chan->set_ref(node->get_value()._ui);
          m_fast.insert(std::make_pair(node->get_value()._ui, chan));
        }
      else
        chan = it->second;
      node->set_chan(chan);
    }
  else if (node->get_type() == LOCAL_CHAN) {
      if ((it = node->get_block()->get_chan().find(node->get_value()._ui)) == node->get_block()->get_chan().end())
        {
          chan = new Chanel();
          chan->set_ref(node->get_value()._ui);
          node->get_block()->get_chan().insert(std::make_pair(node->get_value()._ui, chan));
        }
      else
        chan = it->second;
      node->set_chan(chan);
    }
  else {
      node->set_chan(get_line()->get_chan(node->get_value()._ui));
    }
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
