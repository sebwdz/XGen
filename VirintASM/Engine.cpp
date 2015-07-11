#include    <iostream>

#include    "include/Engine.hpp"
#include    "include/Compilator.hpp"

Engine::Engine() : QObject(), Plugin()
{

}

Engine::~Engine()
{

}

QWidget     *Engine::get_new_widget(std::string &path)
{
    Compilator  *widget;

    widget = new Compilator();
    widget->set_path(path);
    widget->load();
    return (widget);
}

Q_EXPORT_PLUGIN2(Engine, Engine)

