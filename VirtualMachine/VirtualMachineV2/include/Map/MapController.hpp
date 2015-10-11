#ifndef MAPCONTROLLER_HPP
#define MAPCONTROLLER_HPP

# include           "ClassMap.hpp"

class               MapController
{
public:
    MapController();
    ~MapController();

    void            add_obj(ObjectMap *obj);
    void            move_object(ObjectMap *obj);
    void            remove_object(ObjectMap *obj);
    void            clean();
    ClassMap        *get_map();

private:
    ClassMap        *m_map;
};

#endif // MAPCONTROLLER_HPP
