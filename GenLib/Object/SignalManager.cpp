
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Brain.hpp"
#include        "Cell/Module.hpp"
#include        "Object/Signal.hpp"

SignalManager::SignalManager(Object *parent) : Object(parent)
{
  m_sig.insert(std::make_pair(CREAT, &SignalManager::catch_create));
  m_sig.insert(std::make_pair(NEW_HEAD, &SignalManager::catch_create));
  m_sig.insert(std::make_pair(DETACH, &SignalManager::catch_create));
  m_sig.insert(std::make_pair(COMIN, &SignalManager::catch_simple));
}

SignalManager::~SignalManager()
{

}

void            SignalManager::add_signal(unsigned int value, void *ptr)
{
  get_line()->add_signal(value, ptr);
}

void            SignalManager::catch_signals()
{
  boost::unordered_map<unsigned int, SIG_CATCH>::iterator sigit;
  SIGNALS_LIST            &sig = get_line()->get_signals();

  for (unsigned int it = 0; it < sig.size(); it++)
    {
      if ((sigit = m_sig.find(sig[it].first)) != m_sig.end())
        (this->*(sigit->second))(sigit->first, sig[it].second);
    }
  get_ready();
}

void            SignalManager::catch_simple(unsigned int code, void *sig)
{
  if (code == COMIN)
    {
      if (m_parent != sig && CAST(Object*)(sig)->get_parent() != this &&
          CAST(Object*)(sig)->get_type() & TYPE_MODULE)
        {
          CAST(ModuleClass*)(m_parent)->get_map()->remove_object(this);
          CAST(ModuleClass*)(sig)->add_object(this);
          m_parent = CAST(Object*)(sig);
        }
    }
}

void            SignalManager::catch_create(unsigned int code, void *sig)
{
  ModuleClass             *parent;
  ModuleClass             *create;
  Decriptor               *decript;
  int                     it;
  std::vector<SMART(ObjClass)>    &vct = ((GeneticalNode*)sig)->get_son();

  if (m_parent && code != NEW_HEAD)
    parent = CAST(ModuleClass*)(m_parent);
  else if (m_type & TYPE_MOVABLE)
    parent = CAST(ModuleClass*)(this);
  else
    return ;
  if (code != DETACH)
    {
      create = new ModuleClass(parent);
      create->set_pos(get_pos());
      parent->add_object(create);
      parent = create;
    }
  for (it = 0; it < (int)vct.size(); it++)
    {
      decript = new Decriptor(parent);
      decript->set_block(boost::static_pointer_cast<GeneticObj>(vct[it]->copy()));
      decript->get_line()->shared_to_line(get_line());
      decript->set_pos(get_pos());
      if (code != DETACH)
        parent->attach_decriptor(decript);
      else
        parent->add_object(decript);
    }
}
