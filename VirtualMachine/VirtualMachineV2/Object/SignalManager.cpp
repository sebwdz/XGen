
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Brain.hpp"
#include        "Cell/Module.hpp"
#include        "Object/Signal.hpp"

SignalManager::SignalManager(Object *parent) : ObjectMap(parent)
{
    m_sig.insert(std::make_pair(CREAT, &SignalManager::catch_create));
    m_sig.insert(std::make_pair(NEW_HEAD, &SignalManager::catch_create));
    m_sig.insert(std::make_pair(DETACH, &SignalManager::catch_create));
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
    OBJECT_LIST::iterator                       obj;
    boost::unordered_map<unsigned int, SIG_CATCH>::iterator it;
    std::list<void*>::iterator                  arg;
    void                                        *sig;

    for (it = m_sig.begin(); it != m_sig.end(); it++)
    {
        sig = m_line.get_signal(it->first);
        if (sig)
            (this->*(it->second))(it->first, sig);
    }
    get_ready();
}

void            SignalManager::catch_create(unsigned int code, void *sig)
{
    ModuleClass             *parent;
    SMART(ModuleClass)      create;
    SMART(Decriptor)        decript;
    int                     it;
    std::vector<SMART(ObjClass)>    &vct = ((GeneticalNode*)sig)->get_son();

    if (m_parent && (parent = CAST(ModuleClass*)(m_parent)) && code != NEW_HEAD)
    {
        while (CAST(ModuleClass*)(parent->get_parent()) && !CAST(Brain*)(parent))
            parent = CAST(ModuleClass*)(parent->get_parent());
    }
    else if (CAST(ModuleClass*)(this))
        parent = CAST(ModuleClass*)(this);
    else
        return ;
    if (code != DETACH)
    {
        create = SMART(ModuleClass)(new ModuleClass(parent));
        create->set_pos(get_pos());
        parent->add_object(create);
        parent = create.get();
    }
    for (it = 0; it < (int)vct.size(); it++)
    {
        decript = SMART(Decriptor)(new Decriptor(parent));
        decript->set_node(boost::static_pointer_cast<GeneticalNode>(vct[it]->copy()));
        decript->get_line()->shared_to_line(get_line());
        decript->set_pos(get_pos());
        parent->add_object(decript);
    }
}
