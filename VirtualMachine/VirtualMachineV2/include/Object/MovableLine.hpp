#ifndef MOVABLELINE_HPP
#define MOVABLELINE_HPP

#include        <stack>
#include        "Object.hpp"

typedef struct  sMovableChan sMovableChan;

#define         CHAN_MOVELIST   boost::unordered_map<unsigned int, sMovableChan*>

struct                                  sMovableChan
{
    boost::unordered_map<Object*, float>                         obj;
    float                                                        total;
    float                                                        have;
    unsigned int                                                 life;
};

class           MovableLine
{
  public:
    MovableLine();
    ~MovableLine();

    void            make();
    void            filter(Object *obj, bool stop = true);
    void            change_chan(unsigned int ref, sMovableChan *move);
    void            exec();
    void            interact_with(class Movable *obj, ChanPropriety *prop);
    void            interact(class Movable *obj);
    void            apply(class Movable *from, ChanPropriety *prop,
                          std::pair<float, float> &vct, std::pair<float, unsigned int> &chan);

    void            set_parent(class Movable* parent);

    class Movable   *get_parent();
    CHANPLIST       &get_inter();

private:
    std::stack<std::pair<ChanPropriety*, Object*> >     m_stoped;
    CHANPLIST                                           m_inter;
    std::pair<float, float>                             m_move;
    CHAN_MOVELIST                                       m_change;
    class Movable                                       *m_parent;
    std::pair<float, float>                             m_vct;
    float                                               m_len;
    std::vector<int>                                    m_range;
};

#endif // MOVABLELINE_HPP