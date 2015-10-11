
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
    USE_LIST::iterator  it;
    Chanel              *chan;

    if (node->get_chan())
        return (node->get_chan());
    if (node->get_type() == FAST_CHAN) {
        if ((it = m_fast.find(node->get_value())) == m_fast.end())
        {
            chan = new Chanel();
            chan->set_ref(node->get_value());
            m_fast.insert(std::make_pair(node->get_value(), chan));
        }
        else
            chan = it->second;
        node->set_chan(chan);
    }
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
    Object          *obj;

    if (code == ATTACH && (!m_parent || CAST(Brain*)(m_parent)))
    {
        parent = static_cast<ModuleClass*>(sig);
        parent->add_object(this);
    }
}

void        Decriptor::catch_duplic(unsigned int code, void *sig)
{
    (void)code;
    (void)sig;
}
