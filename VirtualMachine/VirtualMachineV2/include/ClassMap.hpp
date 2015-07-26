
#ifndef         CLASS_MAP_HPP
# define        CLASS_MAP_HPP

# include       "Object/ObjectMap.hpp"

typedef class ClassCase         ClassCase;
enum                            LnkDir { UP, DOWN, LEFT, RIGHT };

class           LnkCase
{
public:
    LnkCase();
    virtual ~LnkCase();

    void        add_obj(SMART(ObjectMap) obj, std::pair<int, int> &pos, LnkDir dir);
    void        set_dir(LnkDir dir, SMART(LnkCase) lnk);
    void        remove();
    SMART(LnkCase)     get_dir(LnkDir dir);

private:
    SMART(LnkCase)     m_dir[4];
};


class           ClassCase : public LnkCase
{
public:
                ClassCase();
                virtual ~ClassCase();

                void                            add_obj(SMART(ObjectMap)   obj);
                SMART(ObjectMap)                remove_obj(ObjectMap *obj);
                std::list<SMART(ObjectMap)>     &get_obj();
                std::pair<int, int>             &get_pos();

private:
    std::list<SMART(ObjectMap)> m_obj;
    std::pair<int, int>         m_pos;
};

class           ClassMap
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
    SMART(LnkCase)  m_begin;
};

#endif
