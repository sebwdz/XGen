
#include        "GeneticalNode.hpp"

GeneticalNode::GeneticalNode(GeneticObj *parent) : GeneticObj(parent)
{
    m_value = 0;
    if (parent)
    {
        set_propriety(parent->get_propriety());
        if (CAST(GeneticalNode*)(parent))
            m_len = parent->get_len() + 1;
    }
}

GeneticalNode::~GeneticalNode()
{
}

void            GeneticalNode::set_len(int len)
{
    OBJ_IT      it;

    m_len = len;
    if (m_len < m_propriety->len)
    {
        for (it = m_son.begin(); it != m_son.end(); it++)
            CAST(GeneticalNode*)((*it).get())->set_len(m_len + 1);
    }
    else
        m_son.clear();
}

void            GeneticalNode::set_value(unsigned int value)
{
    m_value = value;
}

unsigned int    GeneticalNode::get_value()
{
    return (m_value);
}

void        GeneticalNode::load(std::ifstream &stream)
{
    int     nb;

    if (!m_parent)
        GeneticObj::load(stream);
    stream >> m_value;
    stream >> nb;
    for (int it = 0; it < nb; it++)
    {
        m_son.push_back(SMART(GeneticalNode)(new GeneticalNode(this)));
        m_son.back()->load(stream);
    }
}

void        GeneticalNode::save(std::ofstream &stream)
{
    OBJ_IT it;

    if (!m_parent)
        GeneticObj::save(stream);
    stream << m_value << " ";
    stream << m_son.size() << std::endl;
    for (it = m_son.begin(); it != m_son.end(); it++)
    {
        (*it)->save(stream);
    }
}
