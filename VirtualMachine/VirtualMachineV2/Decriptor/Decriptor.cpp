
#include        "Cell/Brain.hpp"
#include        "Decriptor/Decriptor.hpp"

Decriptor::Decriptor(Object *obj) : Movable(obj)
{
    m_jmp = 0;
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
}

void        Decriptor::catch_duplic(unsigned int, void *sig)
{

}
