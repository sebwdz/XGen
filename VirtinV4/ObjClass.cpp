
#include        "obj.hpp"

ObjClass::ObjClass(ObjClass *parent)
{
    m_parent = parent;
}

ObjClass::~ObjClass()
{
}

int         ObjClass::get_type()
{
  return (m_type);
}

void        ObjClass::save_file(std::string &filename)
{
    std::ofstream   file(filename.c_str());

    if (file.is_open())
        save(file);
}

void        ObjClass::load_file(std::string &filename)
{
    std::ifstream   file(filename.c_str());

    if (file.is_open())
        load(file);
    else
        throw (std::string("can't open file"));
}

void            ObjClass::set_parent(ObjClass *parent)
{
    m_parent = parent;
}

void            ObjClass::add_son(SMART(ObjClass) son)
{
    m_son.push_back(son);
}

void            ObjClass::clear()
{
    m_son.clear();
}

SMART(ObjClass) ObjClass::copy(SMART(ObjClass) cp)
{
    return (cp);
}

std::vector<SMART(ObjClass)>    &ObjClass::get_son()
{
    return (m_son);
}
