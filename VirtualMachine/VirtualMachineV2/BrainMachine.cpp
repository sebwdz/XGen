
#include        <boost/thread.hpp>
#include        "BrainMachine.hpp"

BrainMachine::BrainMachine() : VirtualMachine()
{
    m_thread = 0;
    m_start = false;
}

BrainMachine::~BrainMachine()
{

}

VirtualMachine  *BrainMachine::copy()
{
    return (new BrainMachine());
}

void            BrainMachine::exec()
{
    if (!m_start)
    {
        m_continue = true;
        m_start = true;
        boost::thread(&BrainMachine::exec_loop, this);
    }
}

void            BrainMachine::exec_loop()
{
    TESTER_LIST::iterator  it;
    bool        exec;
    int         tmp;
    GeneticObj  *ref;

    exec = false;
    it = m_brains.begin();
    while (m_continue)
    {
        tmp = 0;
        m_mutex.lock();
        it = m_brains.begin();
        if (it != m_brains.end())
        {
            tmp = it->second.first.size();
            ref = it->first;
            exec = true;
        }

        m_mutex.unlock();
        if (exec)
        {
            m_mutexth.lock();
            if (m_thread >= 1 || !tmp)
                exec = false;
            else
            {
                m_thread++;
                m_mutex.lock();
                it->second.second++;
                m_mutex.unlock();
            }
            m_mutexth.unlock();
            if (exec)
            {
                boost::thread(&BrainMachine::exec_brain, this, it);
                exec = false;
            }
            m_mutex.lock();
            if ((it = m_brains.find(ref)) != m_brains.end())
                it++;
            else
                it = m_brains.begin();
            m_mutex.unlock();
        }
        boost::this_thread::sleep(boost::posix_time::millisec(1));
    }
    while (m_thread)
        boost::this_thread::sleep(boost::posix_time::millisec(1));
    m_start = false;
}

void        BrainMachine::stop()
{
    m_continue = false;
}

void        BrainMachine::exec_brain(TESTER_LIST::iterator it)
{
    std::list<SMART(Tester)> lst;
    std::list<SMART(Tester)>::iterator brainit;

    m_mutex.lock();
    brainit = it->second.first.begin();
    if (it->second.first.size() < 10)
        std::advance(brainit, it->second.first.size());
    else
        std::advance(brainit, 10);
    lst.insert(lst.begin(), it->second.first.begin(), brainit);
    it->second.first.erase(it->second.first.begin(), brainit);
    m_mutex.unlock();
    for (brainit = lst.begin(); brainit != lst.end() && m_continue; brainit++)
    {
        (*brainit)->set_view(m_view);
        (*brainit)->exec();
    }
    m_mutexth.lock();
    m_thread--;
    m_mutexth.unlock();
    m_mutex.lock();
    it->second.second--;
    m_mutex.unlock();
}

void             BrainMachine::add_individu(boost::shared_ptr<GeneticalIndividu> individu, GeneticObj *obj)
{
    SMART(Tester)       tester;

    tester = SMART(Tester)(new Tester());
    tester->set_individu(individu);
    m_mutex.lock();
    if (m_brains.find(obj) == m_brains.end())
        m_brains.insert(std::make_pair(obj, std::pair<std::list<SMART(Tester)>, int> ()));
    m_brains[obj].first.push_back(tester);
    m_mutex.unlock();
}

void            BrainMachine::wait_block(GeneticObj *obj)
{
    bool        cont;

    cont = true;
    while (cont && m_start)
    {
        m_mutex.lock();
        if (m_brains.find(obj) == m_brains.end())
            cont = false;
        else if (m_brains[obj].first.size() == 0 && m_brains[obj].second == 0)
            cont = false;
        m_mutex.unlock();
        boost::this_thread::sleep(boost::posix_time::millisec(1));
    }
    m_mutex.lock();
    if (m_brains.find(obj) != m_brains.end())
        m_brains.erase(obj);
    m_mutex.unlock();
}
