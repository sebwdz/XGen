
#include        <iostream>
#include        <QMessageBox>
#include        <QFileDialog>

#include        "include/MenuBar.hpp"
#include        "include/MainWindow.hpp"

MenuBar::MenuBar(QWidget *parent) : QMenuBar(parent)
{
    m_work = new QMenu(this);

    m_work->setTitle("File");
    m_work->addAction("New workspace");
    m_work->addAction("Open workspace");
    m_work->addSeparator();
    m_work->addAction("Save workspace");
    m_work->addSeparator();
    m_work->addAction("Close workspace");
    addMenu(m_work);

    connect(m_work, SIGNAL(triggered(QAction*)), this, SLOT(slot_clicked_work(QAction*)));
}

MenuBar::~MenuBar()
{
    delete m_work;
}

void        MenuBar::new_workspace()
{
    QString     name;
    WorkSpace   *work;

    close_workspace();
    if (Manager::get_manager()->get_workspace())
        return ;
    work = new WorkSpace();
    name = "Main";
    work->set_name(name.toStdString());
    name = QFileDialog::getSaveFileName(dynamic_cast<QWidget*>(parent()));
    if (name.size())
    {
        work->set_path(name.toStdString());
        Manager::get_manager()->set_workspace(work);
        add_widget();
    }
}

void        MenuBar::open_workspace()
{
    WorkSpace   *work;
    std::ifstream   file;
    QString     filename;

    close_workspace();
    if (Manager::get_manager()->get_workspace())
        return ;
    filename = QFileDialog::getOpenFileName(dynamic_cast<QWidget*>(parent()));
    if (filename.size())
    {
        file.open(filename.toStdString().c_str());
        work = new WorkSpace();
        work->load(file);
        Manager::get_manager()->set_workspace(work);
        add_widget();
    }
}

void        MenuBar::add_widget()
{
    MainWidget *widget;

    widget = new MainWidget(0);
    widget->set_folder(Manager::get_manager()->get_workspace());
    ((MainWindow*)parent())->add_widget(widget);
}

void        MenuBar::close_workspace()
{
    int     res;
    if (Manager::get_manager()->get_workspace())
    {
        res = QMessageBox::warning((QWidget*)parent(), "Close Workspace",
                         "Do you want clode the curent workspace without saving ?",
                            QMessageBox::Yes, QMessageBox::Cancel);
        if (res != QMessageBox::Yes)
            return ;
        Manager::get_manager()->close_workspace();
    }
}

void        MenuBar::save_workspace()
{
    std::ofstream   file(Manager::get_manager()->get_workspace()->get_path().c_str());

    if (Manager::get_manager()->get_workspace())
        Manager::get_manager()->get_workspace()->save(file);
}

void        MenuBar::slot_clicked_work(QAction *action)
{
    if (action->text() == "New workspace")
        new_workspace();
    else if (action->text() == "Open workspace")
        open_workspace();
    else if (action->text() == "Save workspace")
        save_workspace();
    else if (action->text() == "Close workspace")
        close_workspace();
}
