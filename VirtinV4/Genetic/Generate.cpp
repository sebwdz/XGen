
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
    node->set_block(NULL);
    for (it = 0; it < m_son.size(); it++)
    {
        node->m_son.push_back(m_son[it]->copy());
        node->m_son.back()->set_parent(node.get());
    }
    for (ass = m_ass.begin(); ass != m_ass.end(); ass++)
      {
        nw = ass->second->copy();
        nw->set_parent(node.get());
        node->m_ass.insert(std::make_pair(ass->first, nw));
      }
    node->set_type(m_type);
    return (node);
}
/*
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
*/
