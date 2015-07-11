
#include        <QLayout>
#include        <QFormLayout>
#include        <QGroupBox>
#include        <QLabel>

#include        "include/PoolPropriety.hpp"

PoolPropriety::PoolPropriety() : QGroupBox("Propriety")
{
    QHBoxLayout     *layoutP;
    QVBoxLayout     *layout;
    QFormLayout     *propriety;
    QVBoxLayout         *label;

    m_pool = 0;
    m_gentetic = new ProprietyWidget();
    m_gentetic->setMaximumWidth(300);
    m_valide = new QPushButton("valide");
    m_len = new QSpinBox();
    m_height = new QSpinBox();
    m_size = new QSpinBox();
    label = new QVBoxLayout();
    layoutP = new QHBoxLayout();
    layout = new QVBoxLayout();
    propriety = new QFormLayout();

    label->addWidget(new QLabel("Pool propriety"));
    propriety->addRow("Pool len", m_len);
    propriety->addRow("Pool height", m_height);
    propriety->addRow("Population size", m_size);
    label->addLayout(propriety);
    layoutP->setAlignment(Qt::AlignTop);
    layoutP->addLayout(label);
    layoutP->addWidget(m_gentetic);
    layout->addLayout(layoutP);
    layout->addWidget(m_valide);
    setLayout(layout);

    setMaximumHeight(300);
    setMaximumWidth(600);

    m_len->setRange(1, 10);
    m_height->setRange(1, 10);
    m_size->setRange(10, 100000);

    connect(m_valide, SIGNAL(clicked()), this, SLOT(valide()));
}

PoolPropriety::~PoolPropriety()
{

}

void            PoolPropriety::set_pool(GeneticalPool *pool)
{
    m_pool = pool;
    m_gentetic->set_pool(m_pool);
    m_height->setValue(m_pool->get_pool_height());
    m_len->setValue(m_pool->get_pool_len());
    m_size->setValue(m_pool->get_size());
}

void            PoolPropriety::change()
{
    m_pool->set_pool_height(m_height->value());
    m_pool->set_pool_len(m_len->value());
    m_pool->set_size(m_size->value());
    std::cout << "set" << std::endl;
}

void            PoolPropriety::valide()
{
    change();
    m_gentetic->change();
}
