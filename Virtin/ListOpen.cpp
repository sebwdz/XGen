
#include        <iostream>
#include        <QMenu>
#include        <QHeaderView>

#include        "include/MainWindow.hpp"
#include        "include/ListOpen.hpp"

ListOpen::ListOpen(QWidget *parent) : QTreeView(parent)
{
    m_menu = new QMenu(this);

    header()->hide();
    setMaximumWidth(240);
    m_model = new ModelListOpen();
    setModel(m_model);

    setContextMenuPolicy(Qt::CustomContextMenu);
    addAction(new QAction("EditFolder", m_menu));

    connect(this, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(execContexMenu(QPoint)));
    connect(m_menu, SIGNAL(triggered(QAction*)), this, SLOT(menu_folder_clicked(QAction*)));
    connect(m_model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(rename(QModelIndex, QModelIndex)));
}

ListOpen::~ListOpen()
{

}

void        ListOpen::set_folder(Folder *folder)
{
    m_model->set_folder(folder);
}

void        ListOpen::update()
{
    m_model->update();
}

void        ListOpen::execContexMenu(QPoint point)
{
    QModelIndex         index = indexAt(point);
    OpenItem            *item;

    m_menu->clear();
    if (index.isValid())
    {
        item = (OpenItem*)m_model->itemFromIndex(index);
        if (dynamic_cast<Folder*>(item->get_file()))
        {
            m_menu->addAction("New folder");
            m_menu->addAction("New element...");
            m_menu->addSeparator();
            m_menu->addAction("Open in new window");
        }
        else
        {
            m_menu->addAction("Open");
        }
        m_menu->addSeparator();
        if (item->get_file()->get_parent())
            m_menu->addAction("Remove");
        m_menu->exec(mapToGlobal(point));
    }
}

void        ListOpen::remove()
{
    OpenItem    *item;

    item = (OpenItem*)m_model->itemFromIndex(currentIndex());
    if (item->get_file()->get_parent())
    {
        item->get_file()->close();
        item->get_file()->get_parent()->remove_file(item->get_file());
    }
}

void        ListOpen::open_file()
{
    OpenItem    *item;

    item = (OpenItem*)m_model->itemFromIndex(currentIndex());
    ((MainWidget*)parent())->open_file(item->get_file());
}

void        ListOpen::menu_folder_clicked(QAction* action)
{
    MainWidget  *widget;
    OpenItem    *item;
    File        *file;

    item = (OpenItem*)m_model->itemFromIndex(currentIndex());
    if (action->text() == "Open in new window")
    {
        widget = new MainWidget(0);
        widget->set_folder(dynamic_cast<Folder*>(item->get_file()));
        ((MainWidget*)parent())->get_main()->add_widget(widget);
    }
    else if (action->text() == "New folder" || action->text() == "New element...")
    {
        if (action->text() == "New folder")
            file = new Folder();
        else
            file = ((MainWidget*)parent())->new_file();
        if (file)
        {
            dynamic_cast<Folder*>(item->get_file())->add_file(file);
            item->get_file()->update();
        }
    }
    else if (action->text() == "Open")
        open_file();
    else if (action->text() == "Remove")
        remove();
}

void        ListOpen::rename(QModelIndex, QModelIndex)
{
    OpenItem    *item;

    item = (OpenItem*)m_model->itemFromIndex(currentIndex());
    item->get_file()->set_name(item->text().toStdString());
    item->get_file()->update();
}
