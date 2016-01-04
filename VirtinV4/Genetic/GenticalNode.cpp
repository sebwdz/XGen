
#include        "GeneticalNode.hpp"

GeneticalNode::GeneticalNode(GeneticObj *parent) : GeneticObj(parent)
{
    m_value._f = 0;
    m_type = 5;
    m_function = NULL;
    m_block = NULL;
}

GeneticalNode::~GeneticalNode()
{
}

void            GeneticalNode::set_block(GeneticalNode *block)
{
  m_block = block;
  if (get_type())
    {
      for (unsigned int it = 0; it < m_son.size(); it++)
        {
          if (m_son[it]->get_type())
            m_son[it]->set_block(m_block);
        }
    }
}

void            GeneticalNode::set_type(int type)
{
  m_type = type;
  if (!type)
    {
      m_local = SMART(GeneticalNode)(new GeneticalNode());
      for (unsigned int it = 0; it < m_son.size(); it++)
        m_son[it]->set_block(this);
    }
}

void            GeneticalNode::set_function(int (Decriptor::*function)(GeneticalNode*))
{
    m_function = function;
}

void            GeneticalNode::set_chan(SMART(GeneticalNode) chan)
{
    m_chan = chan;
}

int             (Decriptor::*GeneticalNode::get_function())(GeneticalNode*)
{
    return (m_function);
}

boost::shared_ptr<GeneticalNode> &GeneticalNode::get_chan()
{
    return (m_chan);
}

std::vector<SMART(GeneticalNode)>   &GeneticalNode::get_son()
{
  return (m_son);
}

SMART(GeneticalNode)        GeneticalNode::get_local()
{
  return (m_local);
}

GeneticalNode    *GeneticalNode::get_block()
{
  return (m_block);
}

SMART(GeneticalNode)    GeneticalNode::get_ass(unsigned int key, bool creat)
{
  boost::unordered_map<unsigned int, SMART(GeneticalNode)>::iterator  it;
  SMART(GeneticalNode)                                                res;

  if ((it = m_ass.find(key)) == m_ass.end())
    {
      if (!creat)
        return (res);
      res = SMART(GeneticalNode)(new GeneticalNode());
      res->set_parent(this);
      m_ass.insert(std::make_pair(key, res));
      m_son.push_back(res);
      return (res);
    }
  return (it->second);
}

SMART(GeneticalNode)                 &GeneticalNode::get_son_ref(unsigned int ref)
{
  SMART(GeneticalNode)          res;

  while (ref >= m_son.size())
    {
      res = SMART(GeneticalNode)(new GeneticalNode());
      res->set_parent(this);
      m_son.push_back(res);
    }
  return (m_son[ref]);
}

void                                GeneticalNode::add_son(boost::shared_ptr<GeneticalNode> son)
{
  son->set_parent(this);
  m_son.push_back(son);
}


void                GeneticalNode::set_ass(unsigned int key, SMART(GeneticalNode) node)
{
  m_ass[key] = node;
}

void                GeneticalNode::remove_ass(unsigned int key)
{
  m_ass.erase(key);
}

USE_LIST                &GeneticalNode::get_ass()
{
  return (m_ass);
}

void        GeneticalNode::load(std::ifstream &stream)
{
    unsigned int     nb;
    int             type;

    stream.read(reinterpret_cast<char*>(&m_value), sizeof(nodeValue));
    stream.read(reinterpret_cast<char*>(&nb), sizeof(unsigned int));
    for (unsigned int it = 0; it < nb; it++)
    {
        stream.read(reinterpret_cast<char*>(&type), sizeof(int));
        m_son.push_back(SMART(GeneticalNode)(new GeneticalNode(this)));
        m_son.back()->load(stream);
        m_son.back()->set_type(type);
    }
}

void        GeneticalNode::save(std::ofstream &stream)
{
    unsigned int    it;
    unsigned int    size;

    size = m_son.size();
    stream.write(reinterpret_cast<const char*>(&m_value), sizeof(nodeValue));
    stream.write(reinterpret_cast<const char*>(&size), sizeof(unsigned int));
    for (it = 0; it < m_son.size(); it++)
    {
        size = m_son[it]->get_type();
        stream.write(reinterpret_cast<char*>(&size), sizeof(int));
        m_son[it]->save(stream);
    }
}
