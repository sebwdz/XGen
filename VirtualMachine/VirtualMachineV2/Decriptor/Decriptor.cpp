
#include        "Cell/Brain.hpp"
#include        "Decriptor/Decriptor.hpp"

Decriptor::Decriptor(Object *obj) : Movable(obj)
{
    m_jmp = 0;
    m_sig.insert(std::make_pair(ATTACH, (SIG_CATCH)(&Decriptor::catch_simple)));
    for (int it = 0; it < FAST_SIZE; it++)
        m_fast[it] = new Chanel();
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

void        Decriptor::set_node(boost::shared_ptr<GeneticalNode> node)
{
    m_node = node;
}

unsigned int    Decriptor::get_value(GeneticalNode *node)
{
    if (node->get_type() != VALUE)
        return (get_chan(node)->get_value());
    return (node->get_value());
}

Chanel*         Decriptor::get_chan(GeneticalNode *node)
{
    if (node->get_chan())
        return (node->get_chan());
    if (node->get_type() == FAST_CHAN && node->get_value() < FAST_SIZE)
        node->set_chan(m_fast[node->get_value()]);
    else
        node->set_chan(get_line()->get_chan(node->get_value()));
    return (node->get_chan());
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
        if ((obj = (CAST(ModuleClass*)(m_parent))->get_obj(this)))
            parent->add_object(obj);
    }
}

void        Decriptor::catch_duplic(unsigned int code, void *sig)
{
    (void)code;
    (void)sig;
}
