#ifndef OBJ_HPP
#define OBJ_HPP

#include    <fstream>
#include    <list>
#include    <boost/smart_ptr/shared_ptr.hpp>

#define     SMART(X) boost::shared_ptr<X>
#define     CAST(X)  dynamic_cast<X>

#define     OBJ_IT  std::list<SMART(ObjClass)>::iterator

class       ObjClass
{
public:
    ObjClass(ObjClass *parent = 0);
    virtual ~ObjClass();

    void            save_file(std::string &filename);
    virtual void    save(std::ofstream &file) = 0;

    void            load_file(std::string &filename);
    virtual void    load(std::ifstream &file) = 0;

    virtual SMART(ObjClass) copy(SMART(ObjClass) cp = SMART(ObjClass)());

    void            set_parent(ObjClass *parent);
    void            add_son(SMART(ObjClass) son);

    void            clear();

    OBJ_IT          get_begin();
    OBJ_IT          get_end();

protected:

    ObjClass                          *m_parent;
    std::list<SMART(ObjClass)>        m_son;

};

#endif // OBJ_HPP
