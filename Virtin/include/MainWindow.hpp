#ifndef MAINWINDOWS_HPP
#define MAINWINDOWS_HPP

#include        <qmainwindow.h>

#include        "MainWidget.hpp"
#include        "Manager/Manager.hpp"

class       MainWindow : public QMainWindow
{
public:

    MainWindow();
    virtual ~MainWindow();

    void             add_widget(MainWidget *widget);
    void             close_widget(MainWidget *widget);

    void            closeEvent(QCloseEvent *);
private:

    MainWidget                      *m_central;
    std::vector<MainWidget*>        m_widget;
};

#endif // MAINWINDOWS_HPP
