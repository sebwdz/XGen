#ifndef BRAINMACHINE_HPP
#define BRAINMACHINE_HPP

#include        <boost/thread.hpp>
#include        <include/Tester.hpp>
#include        <VirtualMachine/VirtualMachine.hpp>

#define         TESTER_LIST      boost::unordered_map<GeneticObj*, std::pair<std::list<SMART(Tester)>, int> >

class           BrainMachine : public VirtualMachine
{
public:

    BrainMachine();
    ~BrainMachine();

    void            exec();
    void            stop();
    VirtualMachine  *copy();
    void            add_individu(GeneticalIndividu *individu, GeneticObj *obj);
    void            wait_block(GeneticObj *obj);

    void            exec_loop();
    void            exec_brain(TESTER_LIST::iterator it);

private:
    TESTER_LIST     m_brains;
    boost::mutex    m_mutex;
    boost::mutex    m_mutexth;
    int             m_thread;
};

#endif // BRAINMACHINE_HPP
