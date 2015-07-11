
#include        "Object/Object.hpp"


Object::Object(Object *parent)
{
    m_parent = parent;
    m_pos.first = 0;
    m_pos.second = 0;
    m_state = STATE_MOVE;
}

Object::~Object()
{

}

void            Object::set_parent(Object *parent)
{
    m_parent = parent;
}

void            Object::set_pos(std::pair<float, float> &pos)
{
    m_pos = pos;
}

Object          *Object::get_parent()
{
    return (m_parent);
}

LineDecript     *Object::get_line()
{
    return (&m_line);
}

std::pair<float, float> &Object::get_pos()
{
    return (m_pos);
}

void                Object::get_ready()
{
    m_line.get_ready();
}
