#ifndef CLASSCASE_HPP
#define CLASSCASE_HPP

# include                       "Object/ObjectMap.hpp"

class                               ClassCase
{
public:
    ClassCase();
    virtual ~ClassCase();

    void                                    set_parent(ClassCase *paent);
    void                                    set_size(int size);
    virtual void                            add_obj(SMART(ObjectMap)   obj);
    virtual SMART(ObjectMap)                remove_obj(ObjectMap *obj);
    std::list<SMART(ObjectMap)>             &get_obj();
    int                                     get_size();
    ClassCase                               *get_parent();

protected:
    std::list<SMART(ObjectMap)>     m_obj;
    int                             m_size;
    ClassCase                       *m_parent;
};


#endif // CLASSCASE_HPP
