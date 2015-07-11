
#include        <iostream>
#include        <fstream>
#include        <QLayout>
#include        <QShortcut>
#include        <QAction>

#include        "EditWidget.hpp"

TextEditor::TextEditor() : QWidget()
{
    QVBoxLayout         *layout;

    layout = new QVBoxLayout();
    m_edit = new QTextEdit(this);
    m_save = new QPushButton("Save");
    m_syntax = new SyntaxHighlighter(m_edit->document());

    layout->addWidget(m_edit);
    layout->addWidget(m_save);
    setLayout(layout);

    connect(m_save, SIGNAL(clicked()), this, SLOT(save()));
}

TextEditor::~TextEditor()
{

}

void            TextEditor::set_path(std::string &path)
{
    m_path = path;
}

void            TextEditor::load()
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

void            TextEditor::save()
{
    std::ofstream   file(m_path.c_str());
    QString         str;
    std::cout << "save" << std::endl;
    str = m_edit->toPlainText();
    file << str.toStdString();
}
