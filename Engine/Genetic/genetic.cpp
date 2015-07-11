#include    "genetic.h"
#include    "include/GeneticWidget.hpp"

Genetic::Genetic() : QObject(), Plugin()
{
}

Genetic::~Genetic()
{

}

QWidget     *Genetic::get_new_widget(std::string &path)
{
    GeneticWidget   *widget;

    widget = new GeneticWidget();
    widget->set_path(path);
    widget->load();
    return (widget);
}

Q_EXPORT_PLUGIN2(Genetic, Genetic)
