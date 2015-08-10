
#include        "ClassMap.hpp"

ObjectMap::ObjectMap(Object *parent) : Object(parent)
{
    m_case = NULL;
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
