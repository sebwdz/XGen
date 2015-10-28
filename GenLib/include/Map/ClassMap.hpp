
#ifndef         CLASS_MAP_HPP
# define        CLASS_MAP_HPP

# include        <boost/bimap.hpp>
# include        "LnkCase.hpp"

# define        MAP             boost::bimap<std::pair<int, int>, LnkCase*>
# define        LEFT_MAP        MAP::left_map

typedef class ClassMap          ClassMap;

class                                           ClassMap : public ClassCase
{
public:
                ClassMap();
                virtual ~ClassMap();

                virtual void                    add_obj(Object *obj);
                void                            cross_lnk(LnkCase *lnk, LnkDir dir);
                void                            remove_object(ObjectMap *obj);
                LnkCase                         *make_lnk(std::pair<int, int> &pos);
protected:

    LnkCase                                     *m_begin;
};

#endif
