
#include        <cstdlib>
#include        "GeneticalAlgo.hpp"

void            GeneticalAlgo::exec(int cycle)
{
    GeneticalIndividu   *individu;
    OBJ_IT              it2;
    double              tmp;

    if (m_son.size() > 3 && m_engine)
    {
        for (int it = 0; it < cycle && m_continue; it++)
        {
            for (it2 = m_son.begin(); it2 != m_son.end() && m_continue; it2++)
            {
                individu = CAST(GeneticalIndividu*)((*it2).get());
                m_engine->add_individu(individu, this);
            }
            m_engine->wait_block(this);
            sort_list();
            tmp = CAST(GeneticalIndividu*)((*m_son.begin()).get())->get_fitness();
            if (tmp > m_best)
                m_best = tmp;
            kill_weak();
            if (m_continue)
                selection();
        }
    }
    if (m_continue)
        generate(m_size / 4);
}

void            GeneticalAlgo::sort_list()
{
    bool                move;
    SMART(ObjClass)     tmp;
    OBJ_IT              it;
    OBJ_IT              prev;

    if (m_son.size() < 2)
        return ;
    move = true;
    while (move)
    {
        move = false;
        for (it = m_son.begin(); it != m_son.end(); it++)
        {
            if ((it != m_son.begin() && CAST(GeneticalIndividu*)((*it).get())->get_fitness() >
                    CAST(GeneticalIndividu*)((*prev).get())->get_fitness()))
            {
                tmp = *it;
                *it = *prev;
                *prev = tmp;
                move = true;
            }
            prev = it;
        }
    }
}

void            GeneticalAlgo::kill_weak()
{
    OBJ_IT      it;
    double      average;

    while ((int)m_son.size() > m_size)
        m_son.pop_back();
    average = 0;
    for (it = m_son.begin(); it != m_son.end(); it++)
        average += CAST(GeneticalIndividu*)((*it).get())->get_fitness();
    std::cout << CAST(GeneticalIndividu*)(m_son.front().get())->get_fitness() << std::endl;
    m_best =  CAST(GeneticalIndividu*)(m_son.front().get())->get_fitness();
    m_average = average / m_son.size();
}

GeneticalIndividu            *GeneticalAlgo::get_individu(double value)
{
    GeneticalIndividu       *ind;
    OBJ_IT                  it;

    while (value)
    {
        for (it = m_son.begin(); it != m_son.end(); it++)
        {
            ind = CAST(GeneticalIndividu*)((*it).get());
            value -= ind->get_fitness() + 0.01;
            if (value <= 0)
                return (ind);
        }
    }
    return (CAST(GeneticalIndividu*)((*m_son.begin()).get()));
}

void            GeneticalAlgo::selection()
{
    double      total;
    double      tmp;
    double      tmp2;
    int         nb;
    std::vector<SMART(ObjClass)>    nodes;
    OBJ_IT                          it;

    total = 1;
    for (it = m_son.begin(); it != m_son.end(); it++)
        total += CAST(GeneticalIndividu*)((*it).get())->get_fitness() + 0.01;
    nb = m_size / 4;
    while (nb > 0)
    {
        tmp = rand() % ((int)total * 2);
        tmp2 = rand() % ((int)total * 2);
        cross(nodes, CAST(GeneticalIndividu*)(get_individu(tmp2)),
                CAST(GeneticalIndividu*)(get_individu(tmp)));
        nb--;
    }
    m_son.insert(m_son.begin(), nodes.begin(), nodes.end());
}

void        GeneticalAlgo::cross(std::vector<SMART(ObjClass)> &node,
                                 GeneticalIndividu *indiv1, GeneticalIndividu *indiv2)
{
    SMART(GeneticalIndividu)   res;

    for (int it = 0; it < 2; it++)
    {
        res = SMART(GeneticalIndividu)(new GeneticalIndividu(this));
        if (it == 0)
            res->cross_node(indiv1, indiv2, false);
        else
            res->cross_node(indiv2, indiv1, false);
       res->mutate(0.01);
       node.insert(node.begin(), res);
    }
}
