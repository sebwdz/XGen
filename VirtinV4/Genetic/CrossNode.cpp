
#include        <cstdlib>
#include        "GeneticalNode.hpp"

void            GeneticalNode::cross_node(GeneticalNode *node1,
                                          GeneticalNode *node2, int cross)
{
    GeneticalNode   *tmp;
    OBJ_IT          it;
    OBJ_IT          it2;

    if (m_len >= m_propriety->len)
        return ;
    if (cross <= 0 && !alea(1000, 400))
    {
        cross = rand() % 10;
        cross_node(node2, node1, cross);
    }
    else
    {
        cross--;
        m_value = node1->get_value();
        it = node1->get_begin();
        it2 = node2->get_begin();
        while (it != node1->get_end())
        {
            if (!cross && it2!= node2->get_end())
                tmp = CAST(GeneticalNode*)((*(it2++)).get());
            else
                tmp = 0;
            cross_child(CAST(GeneticalNode*)((*(it++)).get()), tmp, cross);
        }
    }
}

void        GeneticalNode::cross_child(GeneticalNode *node1, GeneticalNode *node2, int cross)
{
    SMART(ObjClass) node;

    if (node2)
    {
        node = SMART(GeneticalNode)(new GeneticalNode(this));
        CAST(GeneticalNode*)(node.get())->set_len(m_len + 1);
        CAST(GeneticalNode*)(node.get())->cross_node(node1, node2, cross);
    }
    else
    {
        node = node1->copy();
        node->set_parent(this);
        CAST(GeneticObj*)(node.get())->set_propriety(m_propriety);
        CAST(GeneticalNode*)(node.get())->set_len(m_len + 1);
    }
    m_son.push_back(node);
}
