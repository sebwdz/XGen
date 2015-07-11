
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Module.hpp"
#include        "Object/Signal.hpp"

SignalManager::SignalManager(Object *parent) : Object(parent)
{
    m_sig.insert(std::make_pair(CREAT, &SignalManager::catch_create));
    m_sig.insert(std::make_pair(NEW_HEAD, &SignalManager::catch_create));
}

SignalManager::~SignalManager()
{

}

void            SignalManager::catch_create(unsigned int code, void *sig)
{
    ModuleClass         *parent;
    SMART(ModuleClass)  create;
    SMART(Decriptor)    decript;

    if (m_parent && (parent = CAST(ModuleClass*)(m_parent)))
    {
        decript = SMART(Decriptor)(new Decriptor(this));
        decript->set_node((GeneticalNode*)sig);
        if (code == CREAT || (code == NEW_HEAD && CAST(ModuleClass*)(this)))
        {
            create = SMART(ModuleClass)(new ModuleClass());
            CAST(ModuleClass*)(create.get())->add_object(decript);
            create->set_pos(m_pos);
            if (code == CREAT)
                parent->add_object(create);
            else
                CAST(ModuleClass*)(this)->add_object(create);
        }
        else if (code == DETACH)
        {
            decript->set_pos(m_pos);
            parent->add_object(decript);
        }
    }
}
