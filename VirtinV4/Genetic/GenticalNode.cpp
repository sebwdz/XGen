
#include        "GeneticBlock.hpp"

GeneticalNode::GeneticalNode(GeneticObj *parent) : GeneticObj(parent)
{
    m_value = 0;
    m_type = 4;
    m_chan = NULL;
    m_function = NULL;
    m_block = NULL;
}

GeneticalNode::~GeneticalNode()
{
}

void            GeneticalNode::set_block(GeneticBlock *block)
{
  m_block = block;
  for (unsigned int it = 0; it < m_son.size(); it++)
    {
      if (m_son[it]->get_type())
          CAST(GeneticalNode*)(m_son[it].get())->set_block(m_block);
    }
}

void            GeneticalNode::set_value(unsigned int value)
{
    m_value = value;
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

int             (Decriptor::*GeneticalNode::get_function())(GeneticalNode*)
{
    return (m_function);
}

Chanel         *GeneticalNode::get_chan()
{
    return (m_chan);
}

GeneticBlock    *GeneticalNode::get_block()
{
  return (m_block);
}

void        GeneticalNode::load(std::ifstream &stream)
{
    unsigned int     nb;
    int             type;

    stream.read(reinterpret_cast<char*>(&m_value), sizeof(unsigned int));
    stream.read(reinterpret_cast<char*>(&nb), sizeof(unsigned int));
    for (unsigned int it = 0; it < nb; it++)
    {
        stream.read(reinterpret_cast<char*>(&type), sizeof(int));
        if (type)
            m_son.push_back(SMART(GeneticalNode)(new GeneticalNode(this)));
        else
          m_son.push_back(SMART(GeneticBlock)(new GeneticBlock()));
        CAST(GeneticObj*)(m_son.back().get())->set_type(type);
        m_son.back()->load(stream);
    }
}

void        GeneticalNode::save(std::ofstream &stream)
{
    OBJ_IT it;
    unsigned int    size;

    size = m_son.size();
    stream.write(reinterpret_cast<const char*>(&m_value), sizeof(unsigned int));
    stream.write(reinterpret_cast<const char*>(&size), sizeof(unsigned int));
    for (it = m_son.begin(); it != m_son.end(); it++)
    {
        size = (*it)->get_type();
        stream.write(reinterpret_cast<char*>(&size), sizeof(int));
        (*it)->save(stream);
    }
}
