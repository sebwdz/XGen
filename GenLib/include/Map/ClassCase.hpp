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
    int                                     get_size() const;
    LnkCase                                 *get_lnk() const;
    bool                                    get_dist(LnkCase *lnk, MovableLine *move) const;
    void                                    interact_with(MovableLine *move);
    void                                    cross_map(MovableLine *move, LnkCase *lnk);

protected:
    std::list<Object*>            m_obj;
    int                           m_size;
    LnkCase                       *m_parent;
};


#endif // CLASSCASE_HPP
