
#ifndef         CLASS_MAP_HPP
# define        CLASS_MAP_HPP

# include       "Object/ObjectMap.hpp"

enum                            LnkDir { UP, DOWN, LEFT, RIGHT };

class                               ClassCase
{
public:
    ClassCase();
    virtual ~ClassCase();

    void                            add_obj(SMART(ObjectMap)   obj);
    SMART(ObjectMap)                remove_obj(ObjectMap *obj);
    std::list<SMART(ObjectMap)>     &get_obj();

private:
    std::list<SMART(ObjectMap)>     m_obj;
};

class                       LnkCase
{
public:
    LnkCase(bool border);
    virtual ~LnkCase();

    void                    add_obj(SMART(ObjectMap) obj, std::pair<int, int> &pos, LnkDir dir, int turn);
    void                    set_dir(LnkDir dir, LnkCase *lnk);
    void                    set_pos(std::pair<int, int> pos);
    void                    remove();
    std::pair<int, int>     &get_pos();
    LnkCase                 *get_dir(LnkDir dir);
    ClassCase               *get_case();

private:
    LnkCase                 *m_dir[4];
    std::pair<int, int>     m_pos;
    ClassCase               *m_case;
    bool                    m_border;
};

class                                           ClassMap
{
public:
                ClassMap();
                virtual ~ClassMap();

                void                            set_obj(SMART(ObjectMap) obj);
                boost::shared_ptr<ObjectMap>    remove_object(ObjectMap *obj);
                void                            move_object(ObjectMap *obj);
                void                            get_list_obj(std::pair<float, float> pos, std::pair<float, float> dist,
                                                                std::list<SMART(ObjectMap)> &lst);
private:
    SMART(LnkCase)                              m_begin;
};

#endif
