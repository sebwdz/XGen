
#include        <QLayout>
#include        <QFileDialog>
#include        "include/GeneratePopulation.hpp"

GeneratePopulation::GeneratePopulation(QWidget *parent, bool chck) : QDialog(parent)
{
    QVBoxLayout     *layout;
    QHBoxLayout     *path;
    QHBoxLayout     *valide;

    m_path = new QLineEdit();
    m_choose = new QPushButton("...");
    m_valide = new QPushButton("Valide");
    m_cancel = new QPushButton("Cancel");
    m_size = new QSpinBox();
    m_use = new QCheckBox();
    layout = new QVBoxLayout();
    path = new QHBoxLayout();
    valide = new QHBoxLayout();

    if (chck)
    {
        m_use->setHidden(true);
        m_use->setChecked(true);
    }
    else
        m_use->setChecked(false);
    m_use->setText("Use Node");
    m_size->setPrefix("Size : ");
    m_size->setRange(1, 40000);
    m_path->setReadOnly(true);

    path->addWidget(m_path);
    path->addWidget(m_choose);
    valide->addWidget(m_valide);
    valide->addWidget(m_cancel);
    layout->addWidget(m_use);
    layout->addLayout(path);
    layout->addWidget(m_size);
    layout->addLayout(valide);

    setLayout(layout);
    connect(m_choose, SIGNAL(clicked()), this, SLOT(slot_get_file()));
    connect(m_valide, SIGNAL(clicked()), this, SLOT(slot_valide()));
    connect(m_cancel, SIGNAL(clicked()), this, SLOT(slot_cancel()));
}

GeneratePopulation::~GeneratePopulation()
{

}

int                 GeneratePopulation::get_size()
{
    return (m_size->value());
}

QString             GeneratePopulation::get_path()
{
    return (m_path->text());
}

void            GeneratePopulation::slot_get_file()
{
    QString     path;

    path = QFileDialog::getOpenFileName(this);
    if (!path.isEmpty())
        m_path->setText(path);
}

void            GeneratePopulation::slot_valide()
{
    if (!m_use->isChecked() || m_path->text().isEmpty())
        m_path->setText("null");
    close();
}

void            GeneratePopulation::slot_cancel()
{
    m_path->setText("cancel");
    close();
}
