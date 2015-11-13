
#include        "Map/ClassMap.hpp"

ObjectMap::ObjectMap()
{
  m_case = NULL;
  m_pos.first = 0;
  m_pos.second = 0;
}

ObjectMap::~ObjectMap()
{

}

void                    ObjectMap::set_case(ClassCase* mycase)
{
  m_case = mycase;
}

ClassCase               *ObjectMap::get_cases()
{
  return (m_case);
}


void            ObjectMap::set_pos(std::pair<float, float> &pos)
{
  m_pos = pos;
}

std::pair<float, float> &ObjectMap::get_pos()
{
  return (m_pos);
}
