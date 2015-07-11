
#include        "BrainMachine.hpp"
#include        "Engine.hpp"

Engine::Engine() : QObject(), PluginMachine()
{

}

Engine::~Engine()
{

}

VirtualMachine  *Engine::get_machine()
{
    BrainMachine    *engine;

    engine = new BrainMachine();
    return (engine);
}

MachineViewWidget     *Engine::get_view()
{
    BrainView           *view;

    view = new BrainView();
    return (view);
}

QWidget     *Engine::get_new_widget(std::string &path)
{
    return (new QWidget());
}

Q_EXPORT_PLUGIN2(Engine, Engine)

