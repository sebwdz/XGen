
#include        <cstdlib>
#include        "GeneticalNode.hpp"

SMART(GeneticalNode)    GeneticalNode::copy(SMART(GeneticalNode) cp)
{
    SMART(GeneticalNode)    node;
    SMART(GeneticalNode)    nw;
    unsigned int            it;
    USE_LIST::iterator      ass;

    if (!cp)
        node = SMART(GeneticalNode)(new GeneticalNode(NULL));
    else
        node = cp;
    node->m_value = m_value;
    node->m_function = m_function;
    node->m_son.clear();
    node->m_ass.clear();
    node->m_ref = m_ref;
    node->set_block(NULL);
    for (it = 0; it < m_son.size(); it++)
    {
        node->m_son.push_back(m_son[it]->copy());
        node->m_son.back()->set_parent(node.get());
        node->m_son.back()->set_key(m_son[it]->get_key());
        if (m_son[it]->get_key())
            node->m_ass.insert(std::make_pair(m_son[it]->get_key(), node->m_son.back()));
    }
    node->set_type(m_type);
    return (node);
}
