
#ifndef         CLASS_MAP_HPP
# define        CLASS_MAP_HPP

# include        <boost/bimap.hpp>
# include        "LnkCase.hpp"

# define        MAP             boost::bimap<std::pair<int, int>, SMART(LnkCase)>
# define        LEFT_MAP        MAP::left_map

typedef class ClassMap          ClassMap;

class                                           ClassMap : public ClassCase
{
public:
                ClassMap();
                virtual ~ClassMap();

                virtual void                    add_obj(SMART(ObjectMap) obj);
                void                            cross_lnk(LnkCase *lnk, LnkDir dir);
                void                            insert(LnkCase *lnk);
                boost::shared_ptr<ObjectMap>    remove_object(ObjectMap *obj);
                void                            move_object(ObjectMap *obj);
                LnkCase                         *make_lnk(std::pair<int, int> &pos);
                void                            clean();
                LEFT_MAP::iterator              get_begin();
                LEFT_MAP::iterator              get_end();
                void                            get_move_line(Movable *move);
protected:

    SMART(LnkCase)                                    m_begin;
    boost::bimap<std::pair<int, int>, SMART(LnkCase)> m_map;
};

#endif
