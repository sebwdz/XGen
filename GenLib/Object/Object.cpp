
#include        "Object/Object.hpp"


Object::Object(Object *parent) : ObjectMap()
{
  m_parent = parent;
  m_state = STATE_MOVE;
  m_type = 0;
}

Object::~Object()
{

}

void            Object::set_parent(Object *parent)
{
  m_parent = parent;
}

Object          *Object::get_parent()
{
  return (m_parent);
}

LineDecript     *Object::get_line()
{
  return (&m_line);
}

unsigned int    Object::get_type()
{
  return (m_type);
}

void                Object::get_ready()
{
  m_line.get_ready();
}
