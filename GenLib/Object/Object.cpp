
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

void             Object::set_pos(std::pair<float, float> &pos)
{
    m_line.get_chan()->get_ass(Chanel::hash("__pos__"))->get_son_ref(0)->get_value()._f = pos.first;
    m_line.get_chan()->get_ass(Chanel::hash("__pos__"))->get_son_ref(1)->get_value()._f = pos.second;
    ObjectMap::set_pos(pos);
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

void                 Object::get_used(GeneticalNode *node, SMART(GeneticalNode) res)
{
    std::vector<SMART(GeneticalNode)>   &sons = node->get_son();
    SMART(GeneticalNode)                tmp;

    for (unsigned int it = 0; it < sons.size(); it++)
    {
        if (sons[it]->get_type() == GLOBAL_CHAN && sons[it]->get_son().size())
            get_line()->get_chan(sons[it]->get_son()[0]->get_value()._ui)->copy(res->get_ass(sons[it]->get_son()[0]->get_value()._ui));
        get_used(sons[it].get(), res);
    }
}
