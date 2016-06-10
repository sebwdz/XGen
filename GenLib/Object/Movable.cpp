
#include        <cmath>
#include        <boost/unordered_map.hpp>
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Module.hpp"
#include        "Cell/Brain.hpp"


Movable::Movable(Object *parent) : SignalManager(parent)
{
  m_type ^= TYPE_MOVABLE;
  m_moveLine.set_parent(this);
}

Movable::~Movable()
{

}

void            Movable::move()
{
    GeneticalNode       *param;

    m_state = STATE_MOVE;
    if (m_parent && m_parent->get_type() && TYPE_MOVABLE && m_moveLine.get_range().second > 0)
        m_case->get_lnk()->get_map()->cross_map(&m_moveLine, m_case->get_lnk());
    if (m_parent && m_parent->get_type() & TYPE_BRAIN)
    {
        for (unsigned int it = 0; it < get_line()->get_interaction()->get_son().size(); it++)
        {
            param = get_line()->get_interaction()->get_son_ref(it)->get_ass(Chanel::hash("_param")).get();
            if (!param->get_son_ref(LIMIT)->get_value()._f ||
                param->get_son_ref(LIMIT)->get_son_ref(0)->get_value()._f > 0)
            {
                /*if (m_moveLine.can_interact(param, NETWORK))
                    CAST(Brain*)(m_parent)->send_interaction(this, get_line()->get_interaction()->get_son_ref(it).get());*/
            }
        }
    }
}

void            Movable::exec_move()
{
  m_moveLine.exec();
}

void            Movable::make_move_line()
{
  m_state = STATE_EXEC;
  m_moveLine.make();
}

MovableLine     *Movable::get_move_line()
{
  return (&m_moveLine);
}
