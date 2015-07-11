
#include        "include/Manager/Manager.hpp"
#include        "include/Manager/Folder.hpp"

File::File(Folder *parent)
{
    m_parent = parent;
    m_name = "New file";
    m_plugin = 0;
}

File::~File()
{

}

void            File::set_name(std::string name)
{
    m_name = name;
}

std::string     &File::get_name()
{
    return (m_name);
}

void            File::set_path(std::string path)
{
    m_path = path;
}

std::string     &File::get_path()
{
    return (m_path);
}

void            File::set_parent(Folder *parent)
{
    m_parent = parent;
}

Folder          *File::get_parent()
{
    return (m_parent);
}

void            File::set_plugin(s_plugin *plugin)
{
    m_plugin = plugin;
}

Plugin          *File::get_plugin()
{
    if (m_plugin)
        return (m_plugin->plug);
    return (0);
}

void            File::update()
{
    m_parent->update();
}

void            File::close()
{

}

void            File::load(std::ifstream &file)
{
    std::string plug;

    file >> m_name;
    file >> m_path;
    file >> plug;
    if (plug != "null")
        m_plugin = Manager::get_manager()->get_plugin(plug);
}

void            File::save(std::ofstream &file)
{
    file << m_name << std::endl;
    file << m_path << std::endl;
    if (m_plugin)
        file << m_plugin->name << std::endl;
    else
        file << "null" << std::endl;
}
