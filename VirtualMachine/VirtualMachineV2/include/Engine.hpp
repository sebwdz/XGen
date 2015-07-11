#ifndef ENGINE_HPP
#define ENGINE_HPP

#include        "Plugin.hpp"
#include        "BrainView.hpp"

class       Engine : public QObject, public PluginMachine
{
    Q_OBJECT
    Q_INTERFACES(PluginMachine)
public:
    Engine();
    ~Engine();

    VirtualMachine            *get_machine();
    MachineViewWidget         *get_view();
    QWidget                   *get_new_widget(std::string &path);
};

#endif // ENGINE_HPP
