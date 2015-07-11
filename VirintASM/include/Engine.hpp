#ifndef ENGINE_HPP
#define ENGINE_HPP

#include    <QWidget>
#include    "../Virtin/include/Plugin.hpp"

class Engine : public QObject, public Plugin
{
    Q_OBJECT
    Q_INTERFACES(Plugin)

public:
    Engine();
    virtual ~Engine();

    virtual QWidget     *get_new_widget(std::string &path);
};

#endif // ENGINE_HPP
