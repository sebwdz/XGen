
#include        <QTimer>
#include        <QLayout>
#include        "include/StateWidget.hpp"

StateWidget::StateWidget() : QGroupBox("State")
{
    QVBoxLayout     *layout;
    QVBoxLayout     *layoutCur;
    QHBoxLayout     *mainLayout;

    m_state = new QLabel("State : Stoped");
    m_start = new QPushButton("Start");
    m_tournament = new QSpinBox();
    m_turn = new QSpinBox();
    m_max = new QDoubleSpinBox();
    m_average = new QDoubleSpinBox();
    layout = new QVBoxLayout();
    layoutCur = new QVBoxLayout();
    mainLayout = new QHBoxLayout();

    m_tournament->setPrefix("Tournament : ");
    m_turn->setPrefix("Turn : ");
    m_tournament->setRange(1, 100);
    m_turn->setRange(1, 9000);
    m_max->setRange(0, 1000);
    m_average->setRange(0, 1000);
    m_max->setPrefix("Maximum : ");
    m_average->setPrefix("Average : ");
    m_max->setReadOnly(true);
    m_average->setReadOnly(true);

    layoutCur->addWidget(m_max);
    layoutCur->addWidget(m_average);
    layout->addWidget(m_state);
    layout->addWidget(m_tournament);
    layout->addWidget(m_turn);
    layout->addSpacing(10);
    layout->addWidget(m_start);

    mainLayout->addLayout(layout);
    mainLayout->addLayout(layoutCur);
    setLayout(mainLayout);

    m_timer = new QTimer(this);
    m_timer->setInterval(20);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(time_out()));
    connect(m_start, SIGNAL(clicked()), this, SLOT(slot_start()));
}

StateWidget::~StateWidget()
{

}

void        StateWidget::set_pool(GeneticalPool *pool)
{
    m_pool = pool;
}

void        StateWidget::slot_start()
{
    if (m_start->text() == "Start")
    {
        if (!m_engine)
            return ;
        emit begin();
        m_start->setText("Stop");
        m_timer->start();
        m_pool->set_engine(m_engine);
        m_pool->make_pool();
        m_engine->exec();
        m_pool->exec_thread(m_turn->value(), m_tournament->value());
    }
    else
    {
        m_engine->stop();
        m_pool->set_continue(false);
    }
}

void        StateWidget::time_out()
{
    m_pool->check_state();
    m_average->setValue(m_pool->get_average());
    m_max->setValue(m_pool->get_best());
    if (!m_pool->get_start())
    {
        m_engine->stop();
        m_start->setText("Start");
        m_timer->stop();
        emit end();
    }
}

void        StateWidget::up_machine(VirtualMachine *engine)
{
    m_engine = SMART(VirtualMachine)(engine);
}
