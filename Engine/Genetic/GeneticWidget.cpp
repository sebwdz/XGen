
#include        <QLayout>
#include        "include/GeneticWidget.hpp"

GeneticWidget::GeneticWidget() : QWidget()
{
    QVBoxLayout *layout;
    QHBoxLayout *head;

    m_algo = new GeneticalPool();
    m_propriety = new PoolPropriety();
    m_save = new QPushButton("Save");
    m_state = new StateWidget();
    m_population = new PopulationWidget();
    m_engine = new EngineWidget();
    layout = new QVBoxLayout();
    head = new QHBoxLayout();

    head->addWidget(m_engine);
    head->addWidget(m_propriety);
    head->addWidget(m_state);
    layout->addLayout(head);
    layout->addWidget(m_population);
    layout->addWidget(m_save);
    setLayout(layout);

    connect(m_save, SIGNAL(clicked()), this, SLOT(save()));
    connect(m_state, SIGNAL(end()), m_population, SLOT(update_pop()));
    connect(m_engine, SIGNAL(up_machine(VirtualMachine*)), m_state, SLOT(up_machine(VirtualMachine*)));
}

GeneticWidget::~GeneticWidget()
{
    delete m_algo;
}

void        GeneticWidget::set_path(std::string &path)
{
    m_path = path;
}

void        GeneticWidget::load()
{
    m_algo->load_file(m_path);
    m_propriety->set_pool(m_algo);
    m_state->set_pool(m_algo);
    m_population->set_pool(m_algo);
}

void        GeneticWidget::save()
{
    m_algo->save_file(m_path);
}
