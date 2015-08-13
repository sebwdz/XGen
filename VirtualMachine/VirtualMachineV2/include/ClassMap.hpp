
#ifndef         CLASS_MAP_HPP
# define        CLASS_MAP_HPP

# include        <boost/bimap.hpp>
# include       "Object/Movable.hpp"

# define        INV_DIR(X)      (LnkDir)(X & 1 ? X - 1 : X + 1)
# define        MAP             boost::bimap<std::pair<int, int>, SMART(LnkCase)>
# define        LEFT_MAP        MAP::left_map

enum                            LnkDir { UP, DOWN, LEFT, RIGHT, NONE, ALL};

typedef class ClassMap          ClassMap;

class                               ClassCase
{
public:
    ClassCase();
    virtual ~ClassCase();

    virtual void                            add_obj(SMART(ObjectMap)   obj);
    virtual SMART(ObjectMap)                remove_obj(ObjectMap *obj);
    std::list<SMART(ObjectMap)>             &get_obj();

private:
    std::list<SMART(ObjectMap)>     m_obj;
};

class                       LnkCase
{
public:
    LnkCase(LnkDir border, ClassMap *map);
    virtual ~LnkCase();

    LnkCase                 *get_next(LnkDir dir, std::pair<int, int> &pos, bool create, bool cross);
    void                    set_dir(LnkDir dir, LnkCase *lnk);
    void                    set_pos(std::pair<int, int> pos);
    void                    set_case(ClassCase *newCase);
    void                    remove();
    std::pair<int, int>     &get_pos();
    LnkCase                 *get_dir(LnkDir dir);
    ClassCase               *get_case();
    LnkDir                  get_border();

private:
    LnkCase                 *m_dir[4];
    std::pair<int, int>     m_pos;
    ClassCase               *m_case;
    LnkDir                  m_border;
    ClassMap                *m_map;
};

class                                           ClassMap
{
public:
                ClassMap();
                virtual ~ClassMap();

                virtual void                    add_obj(SMART(ObjectMap) obj);
                void                            cross_lnk(LnkCase *lnk, LnkDir dir);
                void                            insert(LnkCase *lnk);
                boost::shared_ptr<ObjectMap>    remove_object(ObjectMap *obj);
                void                            move_object(ObjectMap *obj);
                LnkCase                         *get_lnk(std::pair<int, int> &pos);
                void                            clean();
                LEFT_MAP::iterator              get_begin();
                LEFT_MAP::iterator              get_end();
protected:
    SMART(LnkCase)                                    m_begin;
    boost::bimap<std::pair<int, int>, SMART(LnkCase)> m_map;
};

#endif
