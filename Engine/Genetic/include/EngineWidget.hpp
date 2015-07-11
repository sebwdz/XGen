#ifndef ENGINEWIDGET_HPP
#define ENGINEWIDGET_HPP

#include        <QGroupBox>
#include        <QPushButton>
#include        <QLineEdit>
#include        <VirtualMachine/VirtualMachine.hpp>
#include        "../../Virtin/include/Plugin.hpp"

class           EngineWidget : public QGroupBox
{
    Q_OBJECT
public:

    EngineWidget();
    ~EngineWidget();

public slots:

    void            choose();
    void            edit();

signals:

    void            up_machine(VirtualMachine *machine);

private:

    PluginMachine   *m_plugin;
    QLineEdit       *m_path;
    QPushButton     *m_choose;
    QPushButton     *m_edit;
    SMART(VirtualMachine)  m_machine;
};

#endif // ENGINEWIDGET_HPP
