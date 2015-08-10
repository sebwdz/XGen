

#include        "ClassMap.hpp"

ClassCase::ClassCase()
{

}

ClassCase::~ClassCase()
{

}

void                            ClassCase::add_obj(SMART(ObjectMap) obj)
{
    obj->set_case(this);
    m_obj.push_back(obj);
}

SMART(ObjectMap)                ClassCase::remove_obj(ObjectMap *obj)
{
    std::list<SMART(ObjectMap)>::iterator   it;
    SMART(ObjectMap)                        res;

    for (it = m_obj.begin(); it != m_obj.end(); it++)
    {
        if (obj == it->get())
        {
            res = *it;
            m_obj.erase(it--);
            break;
        }
    }
    return (res);
}

std::list<SMART(ObjectMap)> &ClassCase::get_obj()
{
    return (m_obj);
}
