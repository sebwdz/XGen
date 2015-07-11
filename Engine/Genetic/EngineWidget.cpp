
#include        <QLayout>
#include        <QFileDialog>
#include        "include/EngineWidget.hpp"

EngineWidget::EngineWidget() : QGroupBox()
{
    QVBoxLayout *layout;
    QHBoxLayout *chooseLayout;

    m_choose = new QPushButton("Choose");
    m_edit = new QPushButton("Edit");
    m_path = new QLineEdit();
    layout = new QVBoxLayout();
    chooseLayout = new QHBoxLayout();
    m_plugin = 0;

    m_path->setReadOnly(true);

    chooseLayout->addWidget(m_path);
    chooseLayout->addWidget(m_choose);
    layout->addLayout(chooseLayout);
    layout->addWidget(m_edit);

    setLayout(layout);
    setMaximumWidth(400);
    connect(m_choose, SIGNAL(clicked()), this, SLOT(choose()));
    connect(m_edit, SIGNAL(clicked()), this, SLOT(edit()));
}

EngineWidget::~EngineWidget()
{

}

void        EngineWidget::choose()
{
    std::string      path;
    PluginMachine   *engine;

    path = QFileDialog::getOpenFileName(this).toStdString();
    if (path.size())
    {
        if (m_plugin)
        {
            m_plugin->close();
            m_machine = SMART(VirtualMachine)();
        }
        engine = PluginMachine::load_machine(path);
        if (engine)
        {
            m_plugin = engine;
            m_path->setText(path.c_str());
            m_machine = SMART(VirtualMachine)(m_plugin->get_machine());
        }
        else
            m_path->setText("");
        if (m_machine)
            emit up_machine(m_machine->copy());
        else
            emit up_machine(NULL);
    }
}

void        EngineWidget::edit()
{
    std::string         configure;
    QDialog             *dialog;
    QVBoxLayout         *layout;
    QWidget             *widget;

    if (m_plugin)
    {
        if (!(widget = m_plugin->get_new_widget(configure)))
            return ;
        dialog = new QDialog();
        layout = new QVBoxLayout();
        layout->addWidget(widget);
        dialog->setLayout(layout);
        dialog->exec();
        delete dialog;
    }
}
