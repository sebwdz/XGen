#ifndef EDITWIDGET_HPP
#define EDITWIDGET_HPP

#include        <QPushButton>
#include        <QTextEdit>
#include        "SyntaxHightLighter.hpp"

class           TextEditor : public QWidget
{
    Q_OBJECT
public:
    TextEditor();
    ~TextEditor();

    void            set_path(std::string &path);
    void            load();

public slots:
    void            save();
private:

    QTextEdit           *m_edit;
    QPushButton         *m_save;
    std::string         m_path;
    SyntaxHighlighter   *m_syntax;
};

#endif // EDITWIDGET_HPP
