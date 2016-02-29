#ifndef OBJECT_HPP
#define OBJECT_HPP

#include    <obj.hpp>
#include    "ObjectMap.hpp"
#include    "Decriptor/LineDecrip.hpp"

enum        StateObject { STATE_EXEC, STATE_MOVE };

#define     TYPE_DECRIPTOR    1
#define     TYPE_MODULE       2
#define     TYPE_CELL         4
#define     TYPE_BRAIN        8
#define     TYPE_MOVABLE      16

class       Object : public ObjectMap
{
public:
    Object(Object *parent = 0);
    virtual ~Object();

    virtual void            set_parent(Object *parent);
    Object                  *get_parent();
    void                    set_pos(std::pair<float, float> &pos);

    virtual LineDecript     *get_line();
    unsigned int            get_type();

    void                    get_ready();
    virtual void            exec() = 0;

protected:

    LineDecript             m_line;
    Object                  *m_parent;
    StateObject             m_state;
    unsigned int            m_type;
};

#endif // OBJECT_HPP
