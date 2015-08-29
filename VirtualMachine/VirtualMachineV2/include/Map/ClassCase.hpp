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
    virtual void                            add_obj(SMART(ObjectMap)   obj);
    virtual SMART(ObjectMap)                remove_obj(ObjectMap *obj);
    std::list<SMART(ObjectMap)>             &get_obj();
    int                                     get_size();
    LnkCase                                 *get_lnk();
    virtual void                            get_move_line(MovableLine *move, ClassCase *from, Object *obj);

protected:
    std::list<SMART(ObjectMap)>     m_obj;
    int                             m_size;
    LnkCase                       *m_parent;
};


#endif // CLASSCASE_HPP
