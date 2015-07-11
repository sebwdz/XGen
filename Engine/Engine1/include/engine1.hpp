#ifndef ENGINE1_H
#define ENGINE1_H

#include    <QWidget>
#include    "../../Virtin/include/Plugin.hpp"

class Engine : public QObject, public Plugin
{
    Q_OBJECT
    Q_INTERFACES(Plugin)

public:
    Engine();
    virtual ~Engine();

    virtual QWidget     *get_new_widget(std::string &path);
};

#endif // ENGINE1_H
