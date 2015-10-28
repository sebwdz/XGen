
#include        <cstdlib>
#include        "GeneticalNode.hpp"

SMART(ObjClass)    GeneticalNode::copy(boost::shared_ptr<ObjClass> cp)
{
    SMART(GeneticalNode)    node;
    OBJ_IT                  it;

    if (!cp)
        node = SMART(GeneticalNode)(new GeneticalNode(this));
    else
        node = boost::dynamic_pointer_cast<GeneticalNode>(cp);
    node->m_value = m_value;
    node->m_type = m_type;
    node->m_function = m_function;
    for (it = m_son.begin(); it != m_son.end(); it++)
    {
        node->m_son.push_back((*it)->copy());
        node->m_son.back()->set_parent(node.get());
    }
    return (node);
}
