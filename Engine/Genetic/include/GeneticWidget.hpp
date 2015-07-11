#ifndef GENETICWIDGET_HPP
#define GENETICWIDGET_HPP

# include       <QWidget>
# include       <Genetic/GeneticalPool.hpp>

#include        "include/PoolPropriety.hpp"
#include        "include/StateWidget.hpp"
#include        "include/PopulationWidget.hpp"
#include        "include/EngineWidget.hpp"

class           GeneticWidget : public QWidget
{
    Q_OBJECT
public:
    GeneticWidget();
    ~GeneticWidget();

    void            set_path(std::string &path);
    void            load();

public slots:

    void            save();

private:

    std::string         m_path;
    GeneticalPool       *m_algo;
    PoolPropriety       *m_propriety;
    StateWidget         *m_state;
    PopulationWidget    *m_population;
    EngineWidget        *m_engine;
    QPushButton         *m_save;
};

#endif // GENETICWIDGET_HPP
