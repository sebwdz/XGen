
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

void            GeneticalNode::set_function(SMART(GeneticalNode) (Decriptor::*function)(GeneticalNode*))
{
    m_function = function;
}

void            GeneticalNode::set_chan(SMART(GeneticalNode) chan)
{
    m_chan = chan;
}

SMART(GeneticalNode)             (Decriptor::*GeneticalNode::get_function())(GeneticalNode*)
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

SMART(GeneticalNode)                 GeneticalNode::get_son_ref(unsigned int ref, bool creat)
{
  SMART(GeneticalNode)          res;

  while (ref >= m_son.size())
    {
      if (!creat)
          return (SMART(GeneticalNode)());
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

Serialize *GeneticalNode::serialize()
{
    Serialize       *s = new Serialize;
    Serialize       *tmp;
    unsigned int    size;
    boost::unordered_map<unsigned int, SMART(GeneticalNode)>::iterator  i;

    size = m_son.size();
    s->append((char*)&m_value, sizeof(nodeValue));
    s->append((char*)&m_type, sizeof(int));
    s->append((char*)&size, sizeof(unsigned int));
    for (unsigned int it = 0; it < m_son.size(); it++)
    {
        tmp = m_son[it]->serialize();
        s->append(reinterpret_cast<char*>(tmp->data.data()), tmp->data.size());
        delete tmp;
    }
    size = m_ass.size();
    s->append((char*)&size, sizeof(unsigned int));
    for (i = m_ass.begin(); i != m_ass.end(); i++)
    {
        for (unsigned int it = 0; it < m_son.size(); it++)
        {
            if (i->second == m_son[it])
            {
                s->append((char*)&i->first, sizeof(unsigned int));
                s->append((char*)&it, sizeof(unsigned int));
            }
        }
    }
    return (s);
}

char        *GeneticalNode::deserialize(char *str)
{
    unsigned int    size;
    unsigned int    key[2];

    m_value = *((nodeValue*)str);
    str += sizeof(nodeValue);
    m_type = *((int*)str);
    str += sizeof(int);
    size = *((unsigned int*)str);
    str += sizeof(unsigned int);
    for (unsigned int it = 0; it < size; it++)
        str = get_son_ref(it)->deserialize(str);
    size = *((unsigned int*)str);
    str += sizeof(unsigned int);
    for (unsigned int it = 0; it < size; it++)
    {
        key[0] = *((unsigned int*)str);
        str += sizeof(unsigned int);
        key[1] = *((unsigned int*)str);
        str += sizeof(unsigned int);
        m_ass[key[0]] = m_son[key[1]];
    }
    return (str);
}
