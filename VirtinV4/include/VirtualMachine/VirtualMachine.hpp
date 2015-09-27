#ifndef VIRTUALMACHINE_HPP_INCLUDED
#define VIRTUALMACHINE_HPP_INCLUDED

#include    <boost/thread.hpp>
#include    "Genetic/GeneticalIndividual.hpp"

class       MachineTester
{
public:
    MachineTester() { }
    virtual ~MachineTester() { }
};

class       MachineView
{
public:
    MachineView() { }
    virtual ~MachineView() = 0;

    void            lock() { m_mutex.lock(); }
    void            unlock() { m_mutex.unlock(); }
    virtual void    show_tester(MachineTester *tester) = 0;
    void            set_sleep(int sleep) { m_sleep = sleep; }

protected:
    boost::mutex    m_mutex;
    int             m_sleep;
};

class       VirtualMachine
{
public:
        VirtualMachine();
        virtual ~VirtualMachine();

        virtual void                exec() = 0;
        virtual void                stop() = 0;
        virtual void                set_view(MachineView *view);
        virtual VirtualMachine      *copy() = 0;
        virtual void                add_individu(SMART(GeneticalIndividu) individu, GeneticObj *obj = 0) = 0;
        virtual void                wait_block(GeneticObj *parent = 0) = 0;
        bool                        get_start();
protected:

        bool                        m_continue;
        bool                        m_start;
        MachineView                 *m_view;
};

#endif // VIRTUALMACHINE_HPP_INCLUDED
