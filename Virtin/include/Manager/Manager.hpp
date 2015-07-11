#ifndef MANAGER_HPP
#define MANAGER_HPP

#include        "include/Plugin.hpp"
#include        "WorkSpace.hpp"

class           Manager
{
public:
    ~Manager();
    static Manager *get_manager();

    void            load_plugin();
    void            set_workspace(WorkSpace *work);
    void            close_workspace();
    WorkSpace       *get_workspace();
    s_plugin        *get_plugin(std::string &name);
    s_plugin        *get_plugin(int it);

private:
    Manager();
    WorkSpace               *m_work;
    std::vector<s_plugin*>  m_plugin;

};

#endif // MANAGER_HPP
