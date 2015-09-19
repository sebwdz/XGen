#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include        "Signal.hpp"
#include        "MovableLine.hpp"

class           Movable : public SignalManager
{
public:
    Movable(Object *parent);
    virtual ~Movable();

    virtual void    move();
    virtual void    exec_move();
    void            make_move_line();
    virtual void    get_move_line(MovableLine *move, Object *from);
    MovableLine     *get_move_line();
protected:
    MovableLine     m_moveLine;
};

#endif // MOVABLE_HPP
