#ifndef         MODULE_HPP
#define         MODULE_HPP

#include        "Object/Movable.hpp"
#include        "Cell/Skeleton.hpp"
#include        "ClassMap.hpp"

#define         OBJECT_LIST      std::list<SMART(Object)>

class           ModuleClass : public Movable, public ClassMap
{
public:
    ModuleClass(Object *parent = 0);
    virtual ~ModuleClass();

    void                        add_object(SMART(Object) obj);
    Skeleton                    *get_skeleton();

    void                        make_skeleton();
    virtual void                exec();
    virtual void                catch_signals();
    OBJECT_LIST::iterator       get_begin();
    OBJECT_LIST::iterator       get_end();
    SMART(Object)               get_obj(Object* obj);

    void                        move();
    void                        exec_move();
    void                        get_move_line(MovableLine *move, Object *from);

    virtual void                catch_simple(unsigned int code, void *sig);
    virtual void                catch_duplic(unsigned int, void *sig);
    virtual void                catch_kill(unsigned int code, void *sig);

protected:

    Skeleton                    *m_skel;
    OBJECT_LIST                 m_obj;
};

#endif // MODULE_HPP
