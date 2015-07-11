
#include        <iostream>
#include        <QPluginLoader>
#include        "include/Plugin.hpp"

Plugin::Plugin()
{
    m_load = 0;
}

Plugin      *Plugin::load(std::string &path)
{
    QPluginLoader   *tmp;
    QObject         *plugin;
    Plugin          *res;

    res = 0;
    tmp = new QPluginLoader(path.c_str());
    if ((plugin = tmp->instance()))
        res = qobject_cast<Plugin*>(plugin);
    else
    {
        std::cout << tmp->errorString().toStdString() << std::endl;
        return (0);
    }
    if (res)
        res->m_load = tmp;
    return (res);
}

void        Plugin::close()
{
    if (m_load)
    {
        m_load->unload();
        delete m_load;
        m_load = 0;
    }
}

PluginMachine::PluginMachine() : Plugin()
{

}

PluginMachine   *PluginMachine::load_machine(std::string &path)
{
    QPluginLoader   *tmp;
    QObject         *plugin;
    PluginMachine   *res;

    res = 0;
    tmp = new QPluginLoader(path.c_str());
    if ((plugin = tmp->instance()))
        res = qobject_cast<PluginMachine*>(plugin);
    else
    {
        std::cout << tmp->errorString().toStdString() << std::endl;
        return (0);
    }
    if (res)
        res->m_load = tmp;
    return (res);
}
