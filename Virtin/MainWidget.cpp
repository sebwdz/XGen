
#include        <iostream>
#include        <QMenu>
#include        <QFileDialog>

#include        "include/ChooseElement.hpp"
#include        "include/MainWindow.hpp"
#include        "include/MainWidget.hpp"


MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout     *layout;

    layout = new QHBoxLayout(this);
    m_list = new ListOpen(this);
    m_viewSon = new QTabWidget(this);
    m_menu = new QMenu(this);

    m_viewSon->setContextMenuPolicy(Qt::CustomContextMenu);
    m_viewSon->addAction(new QAction("close", m_menu));

    connect(m_viewSon, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(exec_menu(QPoint)));
    connect(m_menu, SIGNAL(triggered(QAction*)), this, SLOT(click_menu(QAction*)));

    layout->addWidget(m_list);
    layout->addWidget(m_viewSon);
    setLayout(layout);

}

MainWidget::~MainWidget()
{
    m_viewSon->clear();
}

void        MainWidget::set_main(MainWindow *wdw)
{
    m_parent = wdw;
}

void        MainWidget::set_folder(Folder *folder)
{
    folder->add_widget_parent(this);
    m_list->set_folder(folder);
}

MainWindow          *MainWidget::get_main()
{
    return (m_parent);
}

File                *MainWidget::new_file()
{
    File            *file;
    ChooseElement   *wdw;

    wdw = new ChooseElement(this);
    wdw->exec();
    file = wdw->get_file();
    if (file)
    {
        delete wdw;
        open_file(file);
    }
    return (file);
}

void        MainWidget::open_file(File *file)
{
    QWidget *widget;

    if (file->get_plugin())
    {
        widget = file->get_plugin()->get_new_widget(file->get_path());
        if (widget)
            m_viewSon->addTab(widget, file->get_name().c_str());
    }
}

void        MainWidget::close()
{
    m_parent->close_widget(this);
}

void        MainWidget::update()
{
    m_list->update();
}

void        MainWidget::exec_menu(QPoint point)
{
    m_menu->clear();
    m_menu->addAction("close");
    m_menu->exec(m_viewSon->mapToGlobal(point));
}

void        MainWidget::click_menu(QAction *act)
{
    if (act->text() == "close")
    {
        m_viewSon->currentWidget()->close();
        m_viewSon->removeTab(m_viewSon->currentIndex());
    }
}
