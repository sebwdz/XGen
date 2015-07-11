#ifndef LISTOPEN_HPP
#define LISTOPEN_HPP

#include        <QTreeView>

#include        "include/ModelListOpen.hpp"

class           ListOpen : public QTreeView
{
    Q_OBJECT
   public:
    ListOpen(QWidget *parent);
    ~ListOpen();

    void        set_folder(Folder *folder);
    void        update();

    void        remove();
    void        open_file();

public slots:
    void        execContexMenu(QPoint point);
    void        menu_folder_clicked(QAction *);
    void        rename(QModelIndex, QModelIndex);

private:

    ModelListOpen       *m_model;
    QMenu               *m_menu;

};

#endif // LISTOPEN_HPP
