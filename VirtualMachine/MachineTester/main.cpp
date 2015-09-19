
#include        <iostream>
#include        <QApplication>
#include        "Engine.hpp"
#include        "Genetic/GeneticalPool.hpp"
#include        "BrainMachine.hpp"

int             main(int ac, char **av)
{
    PluginMachine      *plugin;
    GeneticalIndividu  *pool;
    VirtualMachine     *engine;
    MachineViewWidget  *widget;
    std::string name;
    QApplication        app(ac, av);

    try {
        if (ac < 2)
            throw (std::string("./Tester node_file"));
        name = "../build-VirtualMachineV2-Desktop-Debug/libGenetic.so";
        plugin = PluginMachine::load_machine(name);
        if (!plugin)
            return (1);
        std::cout << "succes" << std::endl;
        name = av[1];
        pool = new GeneticalIndividu();
        pool->load_file(name);
    } catch (std::string &str)
    {
        std::cout << str << std::endl;
        return (1);
    }
    engine = plugin->get_machine();
    if (!engine)
    {
        std::cout << "error when cast engine" << std::endl;
        return (1);
    }
    if (ac > 2) {
        widget = plugin->get_view();
        engine->set_view(widget);
        widget->show();
    }
    engine->exec();
    //for (int it = 0; it < 10; it++)
        engine->add_individu(pool);
    engine->wait_block();
    plugin->close();
    delete pool;
    return (0);
}
