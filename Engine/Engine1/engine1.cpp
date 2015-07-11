#include    <iostream>
#include    "EditWidget.hpp"

#include    "engine1.hpp"

Engine::Engine() : QObject(), Plugin()
{

}

Engine::~Engine()
{

}

QWidget     *Engine::get_new_widget(std::string &path)
{
    TextEditor  *widget;

    widget = new TextEditor();
    widget->set_path(path);
    widget->load();
    return (widget);
}

Q_EXPORT_PLUGIN2(Engine, Engine)
