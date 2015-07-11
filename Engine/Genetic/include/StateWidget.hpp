#ifndef STATEWIDGET_HPP
#define STATEWIDGET_HPP

#include        <QGroupBox>
#include        <QLabel>
#include        <QSpinBox>
#include        <QPushButton>
#include        <Genetic/GeneticalPool.hpp>

class           StateWidget : public QGroupBox
{
    Q_OBJECT
public:
    StateWidget();
    ~StateWidget();

    void        set_pool(GeneticalPool *pool);


public slots:

    void        slot_start();
    void        time_out();
    void        up_machine(VirtualMachine *engine);

signals:

    void        begin();
    void        end();

private:

    QLabel          *m_state;
    QSpinBox        *m_tournament;
    QSpinBox        *m_turn;
    QDoubleSpinBox  *m_max;
    QDoubleSpinBox  *m_average;
    QPushButton     *m_start;
    GeneticalPool   *m_pool;
    QTimer          *m_timer;
    SMART(VirtualMachine)  m_engine;
};

#endif // STATEWIDGET_HPP
