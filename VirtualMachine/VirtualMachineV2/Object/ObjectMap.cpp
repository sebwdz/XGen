
#include        "ClassMap.hpp"

ObjectMap::ObjectMap(Object *parent) : Object(parent)
{

}

ObjectMap::~ObjectMap()
{

}

std::list<SMART(ClassCase)> &ObjectMap::get_cases()
{
    return (m_cases);
}
