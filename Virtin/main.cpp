
#include    <iostream>
#include    <qapplication.h>
#include    <QtPlugin>
#include    <QPluginLoader>

#include    "include/Plugin.hpp"
#include    "include/MainWindow.hpp"

int main(int ac, char **av)
{
    MainWindow      *window;
    QApplication    app(ac, av);

    Manager::get_manager();
    window = new MainWindow();
    window->show();
    app.exec();
    delete window;
    return (0);
}
