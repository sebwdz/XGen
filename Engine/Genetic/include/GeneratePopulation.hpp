#ifndef GENERATEPOPULATION_HPP
#define GENERATEPOPULATION_HPP

#include        <QLineEdit>
#include        <QPushButton>
#include        <QSpinBox>
#include        <QCheckBox>
#include        <QDialog>

class           GeneratePopulation : public QDialog
{
    Q_OBJECT
public:
    GeneratePopulation(QWidget *parent, bool chck = false);
    ~GeneratePopulation();

    int             get_size();
    QString         get_path();

public slots:

    void            slot_get_file();
    void            slot_valide();
    void            slot_cancel();

private:

    QLineEdit       *m_path;
    QSpinBox        *m_size;
    QCheckBox       *m_use;
    QPushButton     *m_choose;
    QPushButton     *m_valide;
    QPushButton     *m_cancel;
};

#endif // GENERATEPOPULATION_HPP
