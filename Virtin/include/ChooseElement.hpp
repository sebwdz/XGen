#ifndef CHOOSEELEMENT_HPP
#define CHOOSEELEMENT_HPP

#include        <QLayout>
#include        <QListView>
#include        <QStandardItemModel>
#include        <QDialog>
#include        <QLineEdit>

#include        "Manager/OpenFile.hpp"

class           ChooseElement : public QDialog
{
    Q_OBJECT
public:
    ChooseElement(QWidget *parent);
    ~ChooseElement();

    File            *get_file();

    void            get_plugin();

public slots:

    void        cancel();
    void        valide();

private:

    QListView           *m_list;
    QStandardItemModel  *m_model;
    QPushButton         *m_valide;
    QPushButton         *m_cancel;
    QLineEdit           *m_edit;
    File                *m_file;
};

#endif // CHOOSEELEMENT_HPP
