
#include        <iostream>
#include        <QLayout>
#include        "include/MenuBar.hpp"
#include        "include/MainWidget.hpp"
#include        "include/MainWindow.hpp"

MainWindow::MainWindow() :  QMainWindow()
{
    setMinimumSize(900, 700);
    setMenuBar(new MenuBar(this));
    m_central = 0;
}

MainWindow::~MainWindow()
{
}

void             MainWindow::add_widget(MainWidget *widget)
{
    if (!m_central)
    {
        setCentralWidget(widget);
        m_central = widget;
        widget->setParent(this);
    }
    else
        m_widget.push_back(widget);
    widget->set_main(this);
    widget->show();
}

void            MainWindow::close_widget(MainWidget *widget)
{
    if (widget == m_central)
    {
        centralWidget()->deleteLater();
        m_central = 0;
        return ;
    }
    for (int it = 0; it < (int)m_widget.size(); it++)
    {
        if (m_widget[it] == widget)
        {
            m_widget[it]->deleteLater();
            m_widget.erase(m_widget.begin() + it);
            return ;
        }
    }
}

void            MainWindow::closeEvent(QCloseEvent *event)
{
    Manager::get_manager()->close_workspace();
    for (int it = 0; it < (int)m_widget.size(); it++)
        m_widget[it]->close();
}
