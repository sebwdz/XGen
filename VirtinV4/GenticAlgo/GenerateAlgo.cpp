
#include        "GeneticalAlgo.hpp"

void        GeneticalAlgo::generate(int size)
{
    GeneticalIndividu   *ind;

    if (!m_propriety->range.size())
        return ;
    if (!size)
        size = m_size;
    for (int it = 0; it < size; it++)
    {
        m_son.push_back(SMART(GeneticalIndividu)(new GeneticalIndividu(this)));
        ind = CAST(GeneticalIndividu*)(m_son.back().get());
        ind->set_propriety(m_propriety);
        ind->generate();
    }
}

void        GeneticalAlgo::generate(GeneticalIndividu *individu, int size)
{
    SMART(GeneticalIndividu)    cp;
    double                      ratio;

    if (!size)
        size = m_size;
    ratio = 0;
    if (m_propriety->range.size() < 1)
        return ;
    for (int it = 0; it < (int)size; it++)
    {
        cp = boost::dynamic_pointer_cast<GeneticalIndividu>(individu->copy());
        cp->set_parent(this);
        cp->set_propriety(m_propriety);
        cp->mutate(ratio);
        m_son.push_back(cp);
        ratio += 1.0 / size;
    }
}

void        GeneticalAlgo::indject(GeneticalNode *node)
{
    OBJ_IT                  it;
    SMART(GeneticalNode)    cp;

    if (!m_propriety->range.size())
        return ;
    for (it = m_son.begin(); it != m_son.end(); it++)
    {
        cp = boost::dynamic_pointer_cast<GeneticalNode>(node->copy());
        CAST(GeneticalNode*)((*it).get())->move_node(cp, 0, rand() % 1000);
    }
}
