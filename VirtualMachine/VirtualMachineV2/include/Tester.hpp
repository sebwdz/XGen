#ifndef TESTER_HPP
#define TESTER_HPP

#include        "VirtualMachine/VirtualMachine.hpp"
#include        "Cell/CellClass.hpp"
#include        "Cell/Brain.hpp"

class                   Tester : public MachineTester
{
public:
    Tester();
    ~Tester();

    void                                add_module(GeneticalNode *node, std::pair<float, float> &pos, bool sensor);
    void                                set_individu(boost::shared_ptr<GeneticalIndividu> ind);
    void                                set_view(MachineView *view);
    void                                exec();
    Brain                               *get_brain();

private:
    SMART(Brain)                        m_brain;
    SMART(GeneticalIndividu)            m_ind;
    MachineView                         *m_view;
};

#endif // TESTER_HPP
