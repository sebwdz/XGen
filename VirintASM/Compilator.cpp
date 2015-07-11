
#include        <QLayout>
#include        <fstream>
#include        <iostream>
#include        "include/Compilator.hpp"

int     make(std::vector<std::string> &str, QTextEdit *);

Compilator::Compilator() : QWidget()
{
    QVBoxLayout     *layout;
    QHBoxLayout     *button;

    layout = new QVBoxLayout();
    button = new QHBoxLayout();
    m_edit = new QTextEdit();
    m_save = new QPushButton("save");
    m_mes = new QTextEdit();
    m_compil = new QPushButton("compil");

    m_mes->setMaximumHeight(200);
    m_mes->setReadOnly(true);
    layout->addWidget(m_edit);
    layout->addWidget(m_mes);
    button->addWidget(m_compil);
    button->addWidget(m_save);
    layout->addLayout(button);
    setLayout(layout);

    connect(m_save, SIGNAL(clicked()), this, SLOT(save()));
    connect(m_compil, SIGNAL(clicked()), this, SLOT(compil()));
}

Compilator::~Compilator()
{

}

void    Compilator::set_path(std::string &path)
{
    m_path = path;
}

void    Compilator::load()
{
    std::ifstream   file(m_path.c_str());
    std::string     buff;

    m_edit->clear();
    while (std::getline(file, buff))
    {
        m_edit->insertPlainText(buff.c_str());
        m_edit->insertPlainText("\n");
    }
}

void    Compilator::save()
{
    std::ofstream   file(m_path.c_str());
    QString         str;

    str = m_edit->toPlainText();
    file << str.toStdString();
}

void    Compilator::compil()
{
    std::string str;
    std::vector<std::string>    conf;
    std::ifstream   file(m_path.c_str());

    save();
    while (std::getline(file, str))
    {
        if (str.find_first_not_of(" \n\t") != std::string::npos)
        {
            if (conf.size())
                str = m_path.substr(0, m_path.find_last_of("\\/") + 1) + str;
            conf.push_back(str);
        }
    }
    make(conf, m_mes);
}
