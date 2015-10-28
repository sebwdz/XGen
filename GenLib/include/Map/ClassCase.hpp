#ifndef CLASSCASE_HPP
#define CLASSCASE_HPP

# include                       "Object/Movable.hpp"

typedef class                   LnkCase LnkCase;

class                               ClassCase
{
public:
    ClassCase();
    virtual ~ClassCase();

    void                                    set_lnk(LnkCase *paent);
    void                                    set_size(int size);
    virtual void                            add_obj(Object   *obj);
    virtual void                            remove_obj(ObjectMap *obj);
    std::list<Object*>                      &get_obj();
    int                                     get_size();
    LnkCase                                 *get_lnk();
    bool                                    get_dist(LnkCase *lnk, MovableLine *move);
    void                                    interact_with(MovableLine *move, Object *obj);
    void                                    cross_map(MovableLine *move, Object *obj, LnkCase *lnk);

protected:
    std::list<Object*>           m_obj;
    int                             m_size;
    LnkCase                         *m_parent;
};


#endif // CLASSCASE_HPP
