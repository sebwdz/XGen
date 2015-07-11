#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include        <stack>
#include        "Signal.hpp"

#define         CHAN_MOVELIST   boost::unordered_map<unsigned int, std::pair<MOVABLE_CHAN, float > >
#define         MOVABLE_CHAN    std::pair<boost::unordered_map<Object*, float>, float >

typedef struct                                          MovableLine
{
    std::stack<std::pair<ChanPropriety*, Object*> >     m_stoped;
    CHANPLIST                                           m_inter;
    std::pair<float, float>                             m_move;
    CHAN_MOVELIST                                       m_change;
    class Movable                                       *m_parent;
    std::pair<float, float>                             m_vct;
    float                                               m_len;
} MoveLine;

class           Movable : public SignalManager
{
public:
    Movable(Object *parent);
    virtual ~Movable();

    virtual void    move();
    virtual void    exec_move();
    void            make_move_line();
    void            filter(MovableLine *line, bool stop = true);
    void            apply(Object *from, ChanPropriety *prop, std::pair<float, float> &vct, std::pair<float, unsigned int> &chan);
    void            interact_with(MovableLine *line, ChanPropriety *prop);
    void            get_interact(MovableLine *move);
    virtual void    get_move_line(MovableLine *move, Object *from);
protected:
    MovableLine     m_moveLine;
};

#endif // MOVABLE_HPP
