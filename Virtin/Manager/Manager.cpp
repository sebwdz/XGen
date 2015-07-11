
#include        <iostream>
#include        "include/Manager/Manager.hpp"

Manager::Manager()
{
    m_work = 0;
    load_plugin();
}

Manager::~Manager()
{
    close_workspace();
}

Manager     *Manager::get_manager()
{
    static Manager instance;
    return (&instance);
}

void        Manager::load_plugin()
{
    std::ifstream   file("plugin.x");
    std::string     buff;
    s_plugin        *plug;
    std::size_t     pos;
    std::size_t     end;

    while (std::getline(file, buff))
    {
        plug = new s_plugin;
        pos = buff.find_first_of(" \t");
        plug->name = buff.substr(0, pos);
        pos++;
        end = buff.find_first_of("\t ", pos);
        plug->icon = buff.substr(pos, end);
        pos = end + 1;
        end = buff.find_first_of("\t ", pos);
        plug->path = buff.substr(pos, end);
        if ((plug->plug = Plugin::load(plug->path)))
            m_plugin.push_back(plug);
    }
}

void            Manager::set_workspace(WorkSpace *work)
{
    m_work = work;
}

void            Manager::close_workspace()
{
    if (m_work)
    {
        m_work->close();
        delete m_work;
        m_work = 0;
    }
}

WorkSpace       *Manager::get_workspace()
{
    return (m_work);
}

s_plugin        *Manager::get_plugin(std::string &name)
{
    for (int it = 0; it < (int)m_plugin.size(); it++)
        if (name == m_plugin[it]->name)
            return (m_plugin[it]);
    return (0);
}

s_plugin        *Manager::get_plugin(int it)
{
    if (it < (int)m_plugin.size())
        return (m_plugin[it]);
    return (0);
}
