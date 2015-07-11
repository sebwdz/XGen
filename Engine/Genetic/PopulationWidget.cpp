
#include        <QLayout>
#include        "include/GeneratePopulation.hpp"
#include        "include/PopulationWidget.hpp"

PopulationWidget::PopulationWidget() : QGroupBox("Population")
{
    QHBoxLayout     *layout;
    QVBoxLayout     *layoutEdit;

    m_list = new QListView();
    m_model = new QStandardItemModel();
    m_generate = new QPushButton("Generate population");
    m_inject = new QPushButton("Inject node");
    m_clear = new QPushButton("Clear population");
    m_individu = new IndividuWidget();
    layout = new QHBoxLayout();
    layoutEdit = new QVBoxLayout();

    m_list->setModel(m_model);
    m_inject->setEnabled(false);
    m_clear->setEnabled(false);

    layoutEdit->addWidget(m_generate);
    layoutEdit->addWidget(m_inject);
    layoutEdit->addWidget(m_clear);
    layout->addLayout(layoutEdit);
    layout->addWidget(m_list);
    layout->addWidget(m_individu);
    setLayout(layout);

    connect(m_generate, SIGNAL(clicked()), this, SLOT(generate_pop()));
    connect(m_clear, SIGNAL(clicked()), this, SLOT(clear_pop()));
    connect(m_inject, SIGNAL(clicked()), this, SLOT(indject_pop()));
}

PopulationWidget::~PopulationWidget()
{

}

void        PopulationWidget::set_pool(GeneticalPool *pool)
{
    m_pool = pool;
    update_pop();
}

void        PopulationWidget::generate_pop()
{
    GeneratePopulation  *dial;
    std::string         path;
    GeneticalIndividu   *ind;
    int                 size;

    dial = new GeneratePopulation(this);
    dial->exec();
    path = dial->get_path().toStdString();
    size = dial->get_size();
    if (!path.size() || path == "cancel")
        return ;
    if (path != "null")
    {
        ind = new GeneticalIndividu();
        ind->load_file(path);
        m_pool->generate(ind, size);
    }
    else
    {
        m_pool->generate(size);
    }
    update_pop();
}

void        PopulationWidget::indject_pop()
{
    GeneticalNode       *node;
    std::string         path;
    GeneratePopulation  *dial;

    dial = new GeneratePopulation(this, true);
    dial->exec();
    path = dial->get_path().toStdString();

    if (!path.size() || path == "cancel")
        return ;

    node = new GeneticalNode();
    node->load_file(path);
    m_pool->indject(node);
    update_pop();
}

void        PopulationWidget::clear_pop()
{
    m_pool->clear();
    update_pop();
}

void        PopulationWidget::update_pop()
{
    QStandardItem       *item;
    bool                on;
    int                 nb;
    OBJ_IT              it;

    it = m_pool->get_begin();
    nb = 0;
    m_model->clear();
    while (it != m_pool->get_end())
    {
        item = new QStandardItem();
        item->setEditable(false);
        item->setText(QString("individu") + QVariant(nb).toString());
        m_model->appendRow(item);
        it++;
        nb++;
    }
    on = false;
    if (m_model->rowCount() > 0)
        on = true;
    m_clear->setEnabled(on);
    m_inject->setEnabled(on);
    export_ind();
}

void        PopulationWidget::export_ind()
{
    std::string     ex;
    SMART(ObjClass)          parent;
    OBJ_IT                      max;;

    m_pool->sort_list();
    ex = "res.node";
    if (m_pool->get_begin() == m_pool->get_end())
        return ;

    parent = m_pool->get_begin()->get()->copy();
    parent->set_parent(0);
    CAST(GeneticObj*)(parent.get())->set_propriety(m_pool->get_propriety());
    parent->save_file(ex);
}
