#ifndef MOVABLE_HPP
#define MOVABLE_HPP

#include        "Signal.hpp"

#define         MOVABLE_CHAN    std::pair<boost::unordered_map<Object*, float>, float >

typedef struct                                          MovableLine
{
    std::list<std::pair<unsigned int, Object*> >        m_stoped;
    std::pair<std::pair<float, float>, int>             m_move;
    boost::unordered_map<unsigned int, MOVABLE_CHAN >   m_change;
    class Movable                                       *m_parent;
    std::pair<float, float>                             m_vct;
    float                                               m_len;
} MoveLine;

class           Movable : public SignalManager
{
public:
    Movable(Object *parent);
    ~Movable();

    virtual void    move();
    void            make_move_line();
    void            filter(MovableLine *line, bool stop = true);
    void            apply(float pow, chanPropriety* prop, Object *from, unsigned int chan);
    void            interact_with(MovableLine *from, MovableLine *to, Chanel *chan, MovableLine *stp);
    void            get_interact(MovableLine *move);
    virtual void    get_move_line(MovableLine *move, Object *from);
    bool            is_stop(unsigned int chan);
protected:
    MovableLine     m_moveLine;
};

#endif // MOVABLE_HPP
