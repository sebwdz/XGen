
#include        "Decriptor/chanel.hpp"
#include        "Genetic/GeneticBlock.hpp"

GeneticBlock::GeneticBlock() : GeneticObj()
{
  m_obj = SMART(GeneticalNode)();
  m_type = 0;
}

GeneticBlock::~GeneticBlock()
{
  for (USE_LIST::iterator it = m_chan.begin(); it != m_chan.end(); it++)
    delete it->second;
}

void          GeneticBlock::set_obj(SMART(GeneticObj) obj)
{
  m_obj = obj;
}

SMART(GeneticObj) GeneticBlock::get_obj()
{
  return (m_obj);
}

USE_LIST      &GeneticBlock::get_chan()
{
  return (m_chan);
}

void          GeneticBlock::load(std::ifstream &file)
{
  int         type;

  file.read(reinterpret_cast<char*>(&type), sizeof(int));
  if (type)
      m_obj = SMART(GeneticalNode)(new GeneticalNode(this));
  else
    m_obj = SMART(GeneticBlock)(new GeneticBlock());
  m_obj->load(file);
  m_obj->set_type(type);
  if (m_obj->get_type())
    CAST(GeneticalNode*)(m_obj.get())->set_block(this);
}

void          GeneticBlock::save(std::ofstream &file)
{
  int         type;

  type = m_obj->get_type();
  file.write(reinterpret_cast<const char*>(&type), sizeof(int));
  m_obj->save(file);
}
