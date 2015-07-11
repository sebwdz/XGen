#ifndef FILE_HPP
#define FILE_HPP

#include    <string>
#include    <vector>
#include    <fstream>

#include        "include/Plugin.hpp"


typedef struct  s_plugin
{
    std::string path;
    std::string name;
    std::string icon;
    Plugin     *plug;
} s_plugin;


typedef class Folder Folder;

class           File
{
public:
    File(Folder *parent = 0);
    virtual ~File();

    void            set_name(std::string name);
    std::string     &get_name();
    void            set_path(std::string path);
    std::string     &get_path();
    void            set_parent(Folder *parent);
    Folder          *get_parent();
    void            set_plugin(s_plugin *plugin);
    Plugin          *get_plugin();

    virtual void            close();
    virtual void            update();

    virtual void            load(std::ifstream &file);
    virtual void            save(std::ofstream &file);

protected:

    Folder                      *m_parent;
    std::string                 m_name;
    std::string                 m_path;
    s_plugin                    *m_plugin;
};

#endif // FILE_HPP
