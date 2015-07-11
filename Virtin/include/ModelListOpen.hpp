#ifndef MODELLISTOPEN_HPP
#define MODELLISTOPEN_HPP

#include        <QStandardItemModel>

#include        "include/Manager/WorkSpace.hpp"

class       OpenItem : public QStandardItem
{
public:
    OpenItem();
    ~OpenItem();

    void        set_file(File *file);
    File        *get_file();

private:

    File      *m_file;
};

class       ModelListOpen : public QStandardItemModel
{
public:
    ModelListOpen();
    ~ModelListOpen();

    void        set_folder(Folder *folder);
    void        make_item(OpenItem *parent, File *file);
    void        update();

private:

    Folder      *m_folder;

};

#endif // MODELLISTOPEN_HPP
