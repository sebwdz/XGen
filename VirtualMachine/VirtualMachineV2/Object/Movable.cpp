
#include        <cmath>
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Module.hpp"


Movable::Movable(Object *parent) : SignalManager(parent)
{
    m_moveLine.set_parent(this);
}

Movable::~Movable()
{

}

void            Movable::move()
{
    m_state = STATE_MOVE;
    if (m_parent && CAST(Movable*)(m_parent) && m_moveLine.get_inter().size())
        get_move_line(&m_moveLine, this);
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

bool              Movable::check_attach(MovableLine *line, ChanPropriety *prop)
{
    /*
    if (get_line()->get_chan(prop->get_act()[0])->get_value() > 0 &&
            get_line()->get_chan(prop->get_act()[1])->get_value() < 1)
    {
        if (!CAST(Decriptor*)(this) && CAST(Decriptor*)(line->m_parent))
        {
            line->m_parent->add_signal(ATTACH, static_cast<void*>(this));
            return (true);
        }
    }*/
    return (false);
}

void            Movable::get_move_line(MovableLine *move, Object *from)
{
    move->filter(this);
    if (move->get_inter().size() && from != this)
        move->interact(this);
    if (m_parent /*&& m_parent->get_parent() */&& m_parent != from && CAST(Movable*)(m_parent))
    {
        if (move->get_inter().size())
            CAST(Movable*)(m_parent)->get_move_line(move, this);
    }
    move->filter(this, false);
}

MovableLine     *Movable::get_move_line()
{
    return (&m_moveLine);
}
