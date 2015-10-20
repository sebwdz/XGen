
#include        <cstdlib>
#include        "GeneticalNode.hpp"

void        GeneticalNode::mutate(double ratio)
{
    GeneticalNode   *node;
    SMART(GeneticalNode)    creat;
    OBJ_IT          it;

    if (alea(100000, 100000 - (100000 * ratio)))
        m_value = get_alea_range();
    for (it = m_son.begin(); it != m_son.end(); it++)
    {
        node = CAST(GeneticalNode*)((*it).get());
        if (alea(100000, 100000 - (100000 * ratio)))
        {
            if (alea(10, 6))
                move_node(node->copy(), node, rand() % 100);
            if (alea(10, 6))
            {
                m_son.erase(it--);
                continue;
            }
            if (alea(10, 6))
            {
                creat = SMART(GeneticalNode)(new GeneticalNode(node));
                creat->generate();
                node->add_son(creat);
            }
        }
        node->mutate(ratio);
    }
}

int        GeneticalNode::move_node(SMART(ObjClass) cp, GeneticalNode *from, int _move)
{
    GeneticalNode   *to;
    OBJ_IT          it;
    GeneticalNode   *node;

    to = get_obj(_move, from, 0);
    cp->set_parent(to);
    node = CAST(GeneticalNode*)(cp.get());
    node->set_len(to->get_len() + 1);
    for (it = to->m_son.begin(); it != to->m_son.end(); it++)
    {
        if (alea(1000, 700))
        {
            to->m_son.insert(it, cp);
            return (0);
        }
    }
    to->add_son(cp);
    return (_move--);
}

GeneticalNode        *GeneticalNode::get_obj(int &move, GeneticalNode *from, int parent)
{
    int         up;
    GeneticalNode    *tmp;
    OBJ_IT it;

    up = from ? 1 : 0;
    move--;
    tmp = 0;
    if (move <= 0)
        return (this);
    for (it = m_son.begin(); it != m_son.end(); it++)
    {
        if (from == (*it).get())
            up = 1;
        tmp = CAST(GeneticalNode*)((*it).get());
        if (up)
        {
            tmp = tmp->get_obj(move, 0, 1);
            move--;
        }
        if (tmp)
            return (tmp);
    }
    if (!parent)
    {
        if (m_parent && dynamic_cast<GeneticalNode*>(m_parent))
            return (CAST(GeneticalNode*)(m_parent)->get_obj(move, this, 0));
        else
            return (get_obj(move, from, 0));
    }
    return (0);
}
