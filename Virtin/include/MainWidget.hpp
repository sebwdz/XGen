#ifndef MAINWIDGET_HPP
#define MAINWIDGET_HPP

#include        <QWidget>
#include        <QTabWidget>
#include        "Plugin.hpp"
#include        "ListOpen.hpp"

typedef class MainWindow MainWindow;

class       MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget(QWidget *parent);
    ~MainWidget();

    void                set_folder(Folder *folder);
    void                close();
    void                update();
    MainWindow          *get_main();

    File                *new_file();
    void                open_file(File *file);

    void                set_main(MainWindow *wdw);

public slots:
    void                exec_menu(QPoint);
    void                click_menu(QAction *act);
private:

    ListOpen            *m_list;
    MainWindow          *m_parent;
    QMenu               *m_menu;
    QTabWidget          *m_viewSon;
};

#endif // MAINWIDGET_HPP
