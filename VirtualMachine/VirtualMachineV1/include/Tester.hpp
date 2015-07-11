#ifndef TESTER_HPP
#define TESTER_HPP

#include        "Cell/CellClass.hpp"
#include        "Cell/Brain.hpp"
#include        "Environment.hpp"

class                   Tester
{
public:
    Tester();
    ~Tester();

    void                                add_module(GeneticalNode *node, std::pair<float, float> &pos, bool sensor);
    void                                set_individu(GeneticalIndividu *ind);
    void                                set_view(MachineView *view);
    void                                exec();

private:
    SMART(Brain)                        m_brain;
    GeneticalIndividu                   *m_ind;
    MachineView                         *m_view;
    Environment                         *m_env;
};

#endif // TESTER_HPP
