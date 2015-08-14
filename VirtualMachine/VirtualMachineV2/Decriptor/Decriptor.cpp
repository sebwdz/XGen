
#include        "Cell/Brain.hpp"
#include        "Decriptor/Decriptor.hpp"

Decriptor::Decriptor(Object *obj) : Movable(obj)
{
    m_jmp = 0;
    m_sig.insert(std::make_pair(ATTACH, (SIG_CATCH)(&Decriptor::catch_simple)));
}

Decriptor::~Decriptor()
{

}

LineDecript     *Decriptor::get_line()
{
    if (m_parent && !CAST(Brain*)(m_parent))
        return (m_parent->get_line());
    return (&m_line);
}

void        Decriptor::set_node(GeneticalNode *node)
{
    m_node = node;
}

void        Decriptor::catch_signals()
{
    SignalManager::catch_signals();
}

void        Decriptor::catch_simple(unsigned int code, void *sig)
{
    ModuleClass     *parent;
    SMART(Object)   obj;

    if (code == ATTACH && (!m_parent || CAST(Brain*)(m_parent)))
    {
        parent = static_cast<ModuleClass*>(sig);
        if ((obj = (CAST(ModuleClass*)(m_parent))->get_obj(this))) {
            parent->add_object(obj);
        }
    }
}

void        Decriptor::catch_duplic(unsigned int code, void *sig)
{

}
