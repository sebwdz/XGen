#ifndef GENETIC_H
#define GENETIC_H

#include        "../../Virtin/include/Plugin.hpp"

class Genetic : public QObject, public Plugin
{
    Q_OBJECT
    Q_INTERFACES(Plugin)
public:

    Genetic();
    ~Genetic();

    QWidget *get_new_widget(std::string &path);

};

#endif // GENETIC_H
