#ifndef OBJECT_HPP
#define OBJECT_HPP

#include    <obj.hpp>
#include    "Decriptor/LineDecrip.hpp"

enum        StateObject { STATE_EXEC, STATE_MOVE };

class       Object
{
public:
    Object(Object *parent = 0);
    virtual ~Object();

    void                    set_pos(std::pair<float, float> &pos);
    virtual void                    set_parent(Object *parent);
    Object                  *get_parent();

    std::pair<float, float> &get_pos();
    virtual LineDecript     *get_line();

    void                    get_ready();
    virtual void            exec() = 0;

protected:

    LineDecript             m_line;
    Object                  *m_parent;
    std::pair<float, float> m_pos;
    StateObject             m_state;
};

#endif // OBJECT_HPP
