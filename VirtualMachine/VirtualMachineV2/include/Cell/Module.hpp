#ifndef         MODULE_HPP
#define         MODULE_HPP

#include        "Object/Movable.hpp"
#include        "Cell/Skeleton.hpp"
#include        "Map/MapController.hpp"

#define         OBJECT_LIST      std::vector<Object*>

class           ModuleClass : public Movable
{
public:
    ModuleClass(Object *parent = 0);
    virtual ~ModuleClass();

    void                        add_object(Object *obj);
    Skeleton                    *get_skeleton();

    void                        make_skeleton();
    virtual void                exec();
    OBJECT_LIST::iterator       get_begin();
    OBJECT_LIST::iterator       get_end();
    ClassMap                    *get_map();

    void                        move();
    void                        exec_move();
    void                        get_move_line(MovableLine *move, Object *from);

    virtual void                catch_duplic(unsigned int code, void *sig);
    virtual void                catch_kill(unsigned int code, void *sig);
    virtual void                catch_takeout(unsigned int code, void *sig);
    void                        cal_pos();

protected:

    Skeleton                    *m_skel;
    OBJECT_LIST                 m_obj;
    OBJECT_LIST                 m_decriptor;
    MapController               *m_map;
};

#endif // MODULE_HPP
