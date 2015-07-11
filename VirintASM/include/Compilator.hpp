#ifndef COMPILEUR_HPP
#define COMPILEUR_HPP

#include        <QWidget>
#include        <QTextEdit>
#include        <QPushButton>

class           Compilator : public QWidget
{
    Q_OBJECT
public:
    Compilator();
    ~Compilator();

    void        set_path(std::string &path);
    void        load();
public slots:

    void        save();
    void        compil();

private:

    QTextEdit       *m_edit;
    QTextEdit       *m_mes;
    QPushButton     *m_save;
    QPushButton     *m_compil;
    std::string     m_path;
};

#endif // COMPILEUR_HPP
