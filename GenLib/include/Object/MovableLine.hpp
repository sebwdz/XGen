#ifndef MOVABLELINE_HPP
#define MOVABLELINE_HPP

#include        <stack>
#include        "Object.hpp"

typedef struct  sMovableChan sMovableChan;

#define         CHAN_MOVELIST   boost::unordered_map<GeneticalNode*, sMovableChan*>

struct                                  sMovableChan
{
    boost::unordered_map<Object*, float>                          obj;
    float                                                         total;
    float                                                         have;
    unsigned int                                                  life;
    GeneticalNode*                                                path;
};

class           MovableLine
{
  public:
    MovableLine();
    ~MovableLine();

    void                make();
    void                make_range();
    void                change_chan(GeneticalNode *ref, sMovableChan *move);
    void                exec();
    void                interact_with(class Movable *obj, GeneticalNode *prop);
    void                interact(class Movable *obj, unsigned int scope);
    void                apply(class Movable *from, GeneticalNode *prop,
                          std::pair<float, float> &vct, std::pair<float, GeneticalNode*> &chan);
    bool                check_attach(Object *obj, GeneticalNode *prop);
    void                reduce(float &chan, GeneticalNode *prop);
    bool                can_interact(GeneticalNode *prop, unsigned int scope);

    void                set_parent(class Movable* parent);

    class Movable       *get_parent();
    std::pair<int, int>     &get_range();

private:
    std::pair<float, float>                             m_move;
    CHAN_MOVELIST                                       m_change;
    class Movable                                       *m_parent;
    std::pair<float, float>                             m_vct;
    float                                               m_len;
    std::pair<int, int>                                 m_range;
};

#endif // MOVABLELINE_HPP
