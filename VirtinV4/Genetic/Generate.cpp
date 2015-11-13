
#include        <cstdlib>
#include        "GeneticBlock.hpp"

SMART(ObjClass)    GeneticalNode::copy(boost::shared_ptr<ObjClass> cp)
{
    SMART(GeneticalNode)    node;
    OBJ_IT                  it;

    if (!cp)
        node = SMART(GeneticalNode)(new GeneticalNode(NULL));
    else
        node = boost::static_pointer_cast<GeneticalNode>(cp);
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

SMART(ObjClass)    GeneticBlock::copy(boost::shared_ptr<ObjClass> cp)
{
    SMART(GeneticBlock)    node;

    if (!cp)
        node = SMART(GeneticBlock)(new GeneticBlock());
    else
        node = boost::static_pointer_cast<GeneticBlock>(cp);
    node->set_obj(boost::static_pointer_cast<GeneticObj>(get_obj()->copy()));
    node->get_obj()->set_parent(node.get());
    if (node->get_obj()->get_type())
      CAST(GeneticalNode*)(node->get_obj().get())->set_block(node.get());
    return (node);
}
