
#include        "Genetic/GeneticObj.hpp"

GeneticObj::GeneticObj(GeneticObj *parent) : ObjClass(parent)
{
  m_type = 0;
}

GeneticObj::~GeneticObj()
{
}

int   GeneticObj::get_type()
{
  return (m_type);
}


void            GeneticObj::set_type(int type)
{
    m_type = type;
}
