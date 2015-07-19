
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Brain.hpp"
#include        "Cell/Module.hpp"
#include        "Object/Signal.hpp"

SignalManager::SignalManager(Object *parent) : Object(parent)
{
    m_sig.insert(std::make_pair(CREAT, &SignalManager::catch_create));
    m_sig.insert(std::make_pair(NEW_HEAD, &SignalManager::catch_create));
    m_sig.insert(std::make_pair(DETACH, &SignalManager::catch_create));
}

SignalManager::~SignalManager()
{

}

void            SignalManager::catch_signals()
{
    OBJECT_LIST::iterator                       obj;
    boost::unordered_map<unsigned int, SIG_CATCH>::iterator it;
    std::list<void*>::iterator                  arg;
    std::list<void*>                            sig;

    for (it = m_sig.begin(); it != m_sig.end(); it++)
    {
        sig = m_line.get_signal(it->first);
        for (arg = sig.begin(); arg != sig.end(); arg++)
            (this->*(it->second))(it->first, *arg);
    }
    get_ready();
}

void            SignalManager::catch_create(unsigned int code, void *sig)
{
    ModuleClass         *parent;
    SMART(ModuleClass)  create;
    SMART(Decriptor)    decript;

    if (m_parent && (parent = CAST(ModuleClass*)(m_parent)))
    {
        if (code != NEW_HEAD)
            while (CAST(ModuleClass*)(parent->get_parent()) && !CAST(Brain*)(parent))
                parent = CAST(ModuleClass*)(parent->get_parent());
        decript = SMART(Decriptor)(new Decriptor(parent));
        decript->set_node((GeneticalNode*)sig);
        decript->get_line()->shared_to_line(get_line());
        if (code == CREAT || (code == NEW_HEAD && CAST(ModuleClass*)(this)))
        {
            create = SMART(ModuleClass)(new ModuleClass());
            CAST(ModuleClass*)(create.get())->add_object(decript);
            create->set_pos(m_pos);
            create->set_parent(this);
            create->get_line()->shared_to_line(get_line());
            if (code == CREAT)
                parent->add_object(create);
            else
                CAST(ModuleClass*)(this)->add_object(create);
        }
        else if (code == DETACH)
        {
            decript->set_parent(parent);
            decript->set_pos(m_pos);
            parent->add_object(decript);
        }
    }
}
