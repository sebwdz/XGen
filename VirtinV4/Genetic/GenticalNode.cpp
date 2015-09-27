
#include        "GeneticalNode.hpp"

GeneticalNode::GeneticalNode(GeneticObj *parent) : GeneticObj(parent)
{
    m_value = 0;
    m_type = 0;
    m_chan = NULL;
    m_function = NULL;
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

void            GeneticalNode::set_type(unsigned char type)
{
    m_type = type;
}

void            GeneticalNode::set_function(int (Decriptor::*function)(GeneticalNode*))
{
    m_function = function;
}

void            GeneticalNode::set_chan(Chanel *chan)
{
    m_chan = chan;
}

unsigned int    GeneticalNode::get_value()
{
    return (m_value);
}

unsigned char   GeneticalNode::get_type()
{
    return (m_type);
}

int             (Decriptor::*GeneticalNode::get_function())(GeneticalNode*)
{
    return (m_function);
}

Chanel         *GeneticalNode::get_chan()
{
    return (m_chan);
}

void        GeneticalNode::load(std::ifstream &stream)
{
    unsigned int     nb;

    stream.read(reinterpret_cast<char*>(&m_value), sizeof(unsigned int));
    stream.read(reinterpret_cast<char*>(&m_type), sizeof(unsigned char));
    stream.read(reinterpret_cast<char*>(&nb), sizeof(unsigned int));
    for (unsigned int it = 0; it < nb; it++)
    {
        m_son.push_back(SMART(GeneticalNode)(new GeneticalNode(this)));
        m_son.back()->load(stream);
    }
}

void        GeneticalNode::save(std::ofstream &stream)
{
    OBJ_IT it;
    unsigned int    size;

    size = m_son.size();
    stream.write(reinterpret_cast<const char*>(&m_value), sizeof(unsigned int));
    stream.write(reinterpret_cast<const char*>(&m_type), sizeof(unsigned char));
    stream.write(reinterpret_cast<const char*>(&size), sizeof(unsigned int));
    for (it = m_son.begin(); it != m_son.end(); it++)
    {
        (*it)->save(stream);
    }
}
