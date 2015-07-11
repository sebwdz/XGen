#ifndef POPULATIONWIDGET_HPP
#define POPULATIONWIDGET_HPP

#include        <QGroupBox>
#include        <QListView>
#include        <QPushButton>
#include        <QStandardItemModel>

#include        <Genetic/GeneticalPool.hpp>
#include        "include/InidividuWidget.hpp"

class       PopulationWidget : public QGroupBox
{
    Q_OBJECT
public:
    PopulationWidget();
    ~PopulationWidget();

    void                set_pool(GeneticalPool *pool);

public slots:

    void                generate_pop();
    void                indject_pop();
    void                clear_pop();
    void                update_pop();
    void                export_ind();
private:

    QListView           *m_list;
    QStandardItemModel  *m_model;
    QPushButton         *m_generate;
    QPushButton         *m_inject;
    QPushButton         *m_clear;
    IndividuWidget      *m_individu;
    GeneticalPool       *m_pool;
};

#endif // POPULATIONWIDGET_HPP
