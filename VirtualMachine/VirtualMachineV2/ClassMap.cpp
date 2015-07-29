

#include        "ClassMap.hpp"

ClassMap::ClassMap()
{
    m_begin = SMART(LnkCase)(new LnkCase(true));
}

ClassMap::~ClassMap()
{
}

void        ClassMap::set_obj(SMART(ObjectMap) obj)
{
    std::pair<int, int>     pos;

    pos = obj->get_pos();
    pos.first /= 10;
    pos.second /= 10;
    m_begin->add_obj(obj, pos, RIGHT, 0);
}

SMART(ObjectMap)        ClassMap::remove_object(ObjectMap *obj)
{
    std::list<SMART(ClassCase)>        &lst = obj->get_cases();
    SMART(ObjectMap)        res;

    for(std::list<SMART(ClassCase)>::iterator it = lst.begin(); it != lst.end(); it++)
       res = it->get()->remove_obj(obj);
    lst.clear();
    return (res);
}

void        ClassMap::move_object(ObjectMap *obj)
{
    SMART(ObjectMap)    tmp;

    tmp = remove_object(obj);
    set_obj(tmp);
}

void        ClassMap::get_list_obj(std::pair<float, float> pos, std::pair<float, float> dist,
                           std::list<SMART(ObjectMap)> &lst)
{
    std::pair<int, int>     curpos;

    curpos.first = dist.first + pos.first;
    curpos.second = pos.second;
    do {

    } while (curpos.first != (int)(pos.first + dist.first) || pos.second != 0);
}
