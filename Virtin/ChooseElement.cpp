
#include        <QFileDialog>
#include        <QPushButton>

#include        "include/Manager/Manager.hpp"
#include        "include/ChooseElement.hpp"

ChooseElement::ChooseElement(QWidget *parent) : QDialog(parent)
{
    QHBoxLayout     *layout;
    QVBoxLayout     *secnd;

    secnd = new QVBoxLayout();
    layout = new QHBoxLayout();
    m_list = new QListView();
    m_model = new QStandardItemModel();
    m_valide = new QPushButton("Valide");
    m_cancel = new QPushButton("Cancel");
    m_edit = new QLineEdit(this);
    m_edit->setText("name");

    secnd->addWidget(m_edit);
    secnd->addWidget(m_valide);
    secnd->addWidget(m_cancel);
    m_list->setModel(m_model);
    layout->addWidget(m_list);
    layout->addLayout(secnd);
    setLayout(layout);

    get_plugin();

    connect(m_valide, SIGNAL(clicked()), this, SLOT(valide()));
    connect(m_cancel, SIGNAL(clicked()), this, SLOT(cancel()));

    m_file = 0;
}

ChooseElement::~ChooseElement()
{

}

File        *ChooseElement::get_file()
{
    return (m_file);
}

void        ChooseElement::get_plugin()
{
    QStandardItem   *item;

    for (int it = 0; Manager::get_manager()->get_plugin(it); it++)
    {
        item = new QStandardItem();
        item->setText(Manager::get_manager()->get_plugin(it)->name.c_str());
        item->setIcon(QIcon(Manager::get_manager()->get_plugin(it)->icon.c_str()));
        m_model->appendRow(item);
        item->setEditable(false);
    }
}

void        ChooseElement::cancel()
{
    close();
}

void        ChooseElement::valide()
{
    QModelIndex     index;
    QString         path;

    index = m_list->currentIndex();
    if (index.isValid())
    {
        path = QFileDialog::getSaveFileName(this);
        if (path.size())
        {
            m_file = new File();
            m_file->set_path(path.toStdString());
            m_file->set_name(m_edit->text().toStdString());
            m_file->set_plugin(Manager::get_manager()->get_plugin(index.row()));
            close();
        }
    }
}
