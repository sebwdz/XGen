
#include        "GeneticalPool.hpp"

void        GeneticalPool::make_pool()
{
    GeneticalPool *algo;

    m_pool.clear();
    for (int it = 0; it < m_height && m_poolLen > 0; it++)
    {
        m_pool.push_back(SMART(GeneticalPool)(new GeneticalPool(this)));
        algo = m_pool.back().get();
        algo->set_propriety(m_propriety);
        algo->set_size(m_size / m_height);
        algo->set_pool_len(m_poolLen - 1);
        algo->set_pool_height(m_height);
            algo->set_engine(m_engine);
        algo->make_pool();
    }
}

void        GeneticalPool::check_state()
{
    double  average;

    average = 0;
    for (int it = 0; it < (int)m_pool.size(); it++)
    {
        m_pool[it]->check_state();
        average += m_pool[it]->get_average();
        if (m_pool[it]->get_best() > m_best)
            m_best = m_pool[it]->get_best();
    }
    if (!m_son.size() && m_pool.size())
    {
        average /= (double)m_pool.size();
        m_average = average;
    }
}

void        GeneticalPool::exec_thread(int cycle, int trmt)
{
    if (!m_engine)
        return ;
    set_continue(true);
    m_start = true;
    m_best = 0;
    m_thread = boost::thread(&GeneticalPool::exec, this, cycle, trmt);
}

void        GeneticalPool::exec(int cycle, int trmt)
{
    GeneticalPool   *algo;

    for (int it = 0; it < trmt && m_continue; it++)
    {
        if (m_pool.size() && m_son.size())
            dispatch();
        for (int itp = 0; itp < (int)m_pool.size() && m_continue; itp++)
        {
            algo = m_pool[itp].get();
            if (!m_parent)
                algo->exec_thread(cycle, trmt);
            else
                algo->exec(cycle, trmt);
        }
        for (int itp = 0; itp < (int)m_pool.size(); itp++)
        {
            algo = m_pool[itp].get();
            while (m_pool[itp]->get_start())
                boost::this_thread::sleep(boost::posix_time::milliseconds(10));
            algo->move_population(m_son);
        }
        if (m_continue)
            GeneticalAlgo::exec(cycle);
    }
    sort_list();
    m_start = false;
}

void    GeneticalPool::dispatch()
{
    int     ind;
    int     size;
    OBJ_IT  itr;

    size = m_son.size() / (double)m_pool.size() + 0.5;
    if (size == 0)
        size = 1;
    for (int it = 0; it < (int)m_pool.size() && m_son.size(); it++)
    {
        for (int itp = 0; itp < size && m_son.size(); itp++)
        {
            ind = rand() % m_son.size();
            itr = m_son.begin();
            std::advance(itr, ind);
            m_pool[it]->add_son(*itr);
            m_son.erase(itr);
        }
    }
    m_son.clear();
}
