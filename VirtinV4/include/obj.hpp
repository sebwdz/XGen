#ifndef OBJ_HPP
#define OBJ_HPP

#include    <fstream>
#include    <vector>
#include    <boost/smart_ptr/shared_ptr.hpp>

#define     SMART(X) boost::shared_ptr<X>
#define     CAST(X)  static_cast<X>

#define     OBJ_IT  std::vector<SMART(ObjClass)>::iterator

class       ObjClass
{
public:
    ObjClass(ObjClass *parent = 0);
    virtual ~ObjClass();

    int             get_type();

    void            save_file(std::string const &filename);
    virtual void    save(std::ofstream &file) = 0;

    void            load_file(std::string const &filename);
    virtual void    load(std::ifstream &file) = 0;

    void            set_parent(ObjClass *parent);
    void            add_son(SMART(ObjClass) son);

    void            clear();

protected:

    ObjClass                                          *m_parent;
    int                                               m_type;

};

#endif // OBJ_HPP
