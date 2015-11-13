
#include        <cmath>
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Module.hpp"


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
  m_state = STATE_MOVE;
  if (m_parent && m_parent->get_type() && TYPE_MOVABLE && m_moveLine.get_range().second > 0)
    m_case->get_lnk()->get_map()->cross_map(&m_moveLine, m_parent, m_case->get_lnk());
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
