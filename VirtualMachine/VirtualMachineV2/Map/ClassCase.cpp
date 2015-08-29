

#include        "Map/ClassMap.hpp"

ClassCase::ClassCase()
{
    m_parent = NULL;
}

ClassCase::~ClassCase()
{

}

void                            ClassCase::set_lnk(LnkCase *parent)
{
    m_parent = parent;
}

void                            ClassCase::set_size(int size)
{
    m_size = size;
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
            return (res);
        }
    }
    return (SMART(ObjectMap)());
}

std::list<SMART(ObjectMap)> &ClassCase::get_obj()
{
    return (m_obj);
}

int                         ClassCase::get_size()
{
    return (m_size);
}

LnkCase                   *ClassCase::get_lnk()
{
    return (m_parent);
}

void                        ClassCase::get_move_line(MovableLine *move, ClassCase *from, Object *obj)
{
    std::list<SMART(ObjectMap)>::iterator it;

    for (it = m_obj.begin(); it != m_obj.end(); it++)
    {
        if (CAST(Movable*)(it->get()))
            CAST(Movable*)(it->get())->get_move_line(move, CAST(Movable*)(obj));
    }
    if (m_parent && from != m_parent->get_map())
    {
        m_parent->get_map()->get_move_line(move, this, obj);
    }
}
