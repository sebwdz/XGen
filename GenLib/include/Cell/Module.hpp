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
    void                        attach_decriptor(Decriptor *decriptor);
    Skeleton                    *get_skeleton();

    void                        make_skeleton();
    virtual void                exec();
    OBJECT_LIST::iterator       get_begin();
    OBJECT_LIST::iterator       get_end();
    ClassMap                    *get_map() const;
    const std::vector<ModuleClass *> &get_links() const;

    void                        remove_object(Object *obj);
    void                        move();
    void                        move_object(Object* obj);
    void                        exec_move();
    void                        link(ModuleClass *obj, bool link);
    void                        set_split(ModuleClass *obj, bool split);
    void                        set_spliter(ModuleClass *spliter);

    virtual void                catch_duplic(unsigned int code, void *sig);
    virtual void                catch_kill(unsigned int code, void *sig);
    virtual void                catch_link(unsigned int code, void *sig);
    virtual void                catch_takeout(unsigned int code, void *sig);
    virtual void                catch_split(unsigned int code, void *sig);
    void                        cal_pos();
    void                        change_pos(std::pair<float, float> &pos);

protected:

    Skeleton                    *m_skel;
    OBJECT_LIST                 m_obj;
    OBJECT_LIST                 m_decriptor;
    MapController               *m_map;
    std::vector<ModuleClass*>   m_links;
    ModuleClass                 *m_spliter;
    std::vector<ModuleClass*>   m_split;
};

#endif // MODULE_HPP
