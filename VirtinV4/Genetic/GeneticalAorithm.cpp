#include    <sstream>
#include    <dirent.h>
#include "include/Genetic/GeneticalAorithm.hpp"

GeneticAlgorithm::GeneticAlgorithm()
{
    m_best = 0;
    for (unsigned int it = 0; it < 32; it++)
    {
        m_thread.push_back(new boost::thread(&GeneticAlgorithm::threadWork, this));
    }
}

GeneticAlgorithm::~GeneticAlgorithm()
{

}

void                        GeneticAlgorithm::load()
{
    SMART(Individu)         ind;
    DIR                     *rep;
    struct dirent           *ent;

    rep = opendir("./pop");
    if (rep != NULL)
    {
        while ((ent = readdir(rep)) != NULL)
        {
            if (ent->d_name[0] != '.')
            {
                ind = SMART(Individu)(new Individu);
                ind->setFile(std::string("./pop/") + ent->d_name);
                m_pop.push_back(ind);
            }
        }
        closedir(rep);
    }
}

void                        GeneticAlgorithm::generate(unsigned int size)
{
    SMART(Individu)         ind;

    if (m_patern)
    {
        while (m_pop.size() < size)
        {
            std::stringstream       str;
            str << "./pop/ind" << rand() << ".gen";
            ind = SMART(Individu)(new Individu);
            ind->setFile(str.str());
            ind->generateByPatern(m_patern.get());
            ind->save();
            ind->unload();
            m_pop.push_back(ind);
        }
    }
}

void                        GeneticAlgorithm::setPatern(boost::shared_ptr<GeneticalNode> patern)
{
    m_patern = patern;
}

Individu                    *GeneticAlgorithm::selection(Individu *prev)
{
    float                   sum;
    float                   r;
    Individu                *ind;
    unsigned int            it;

    sum = 0;
    for (it = 0; it < m_pop.size(); it++)
        sum += it * 2;
    do {
        ind = NULL;
        if (sum)
            r = rand() % (int)(sum);
        else
            r = 1;
        it = 0;
        while (r > 0 && it < m_pop.size())
        {
            ind = m_pop[it].get();
            r -= it * 2;
            it++;
        }
    } while (ind != prev && !ind);
    return (ind);
}

bool                        comp_ind(SMART(Individu) ind1, SMART(Individu) ind2)
{
    if (ind1->getScore() < ind2->getScore())
        return (true);
    return (false);
}

void                        GeneticAlgorithm::exec(unsigned int size)
{
    std::pair<Individu*, Individu*>   ind;
    std::vector<SMART(Individu)>      res;
    SMART(Individu)                   tmp;
    unsigned int                      limit;
    float                             sum = 0;

    limit = size / 8;
    evaluate();
    std::sort(m_pop.begin(), m_pop.end(), &comp_ind);
    for (unsigned int it = 0; it < m_pop.size() - size; it++)
        remove(m_pop[it]->getFile().c_str());
    m_pop.erase(m_pop.begin(), m_pop.begin() + (m_pop.size() - size));
    for (unsigned int it = 0; it < m_pop.size(); it++)
        sum += m_pop[it]->getScore();
    std::cout << "average : " << sum / m_pop.size() << std::endl;
    for (unsigned int it = 0; it < limit; it++)
    {
        std::stringstream       str;

        ind.first = selection();
        ind.second = selection(ind.first);
        ind.first->load();
        ind.second->load();
        tmp = ind.first->cross(ind.second, m_patern.get());
        tmp->mutate(m_patern.get());
        str << "./pop/ind" << rand() << ".gen";
        tmp->setFile(str.str());
        tmp->save();
        tmp->unload();
        res.push_back(tmp);
        tmp = ind.second->cross(ind.first, m_patern.get());
        tmp->mutate(m_patern.get());
        str.str("");
        str << "./pop/ind" << rand() << ".gen";
        tmp->setFile(str.str());
        tmp->save();
        tmp->unload();
        res.push_back(tmp);
        ind.first->unload();
        ind.second->unload();
    }
    m_pop.insert(m_pop.begin(), res.begin(), res.end());
}

void                        GeneticAlgorithm::evaluate()
{
    float                     sum;

    sum = 0;
    for (unsigned int it = 0; it < m_pop.size(); it++)
    {
        if (!m_pop[it]->getCalculate())
            sum++;
    }
    m_count = 0;
    for (unsigned int it = 0; it < m_pop.size(); it++)
    {
        if (!m_pop[it]->getCalculate())
        {
            boost::mutex::scoped_lock                   lock(m_lockwork);
            m_var.notify_all();
            m_count++;
            m_work.push_back(m_pop[it].get());
        }
    }
    while (m_count)
        sleep(1);
}

Individu            *GeneticAlgorithm::getNext()
{
    boost::mutex::scoped_lock                   lock(m_lockwork);
    Individu                                    *res;

    res = NULL;
    if (m_work.size())
    {
        res = m_work.back();
        m_work.pop_back();
    }
    return (res);
}


void                GeneticAlgorithm::threadWork()
{
    Individu        *ind;

    while (1)
    {
        while (!(ind = getNext()))
        {
            boost::unique_lock<boost::mutex>    lock (m_sleep);
            m_var.wait(lock);
        }
        ind->evaluate();
        {
            boost::mutex::scoped_lock           lock(m_lockwork);

            m_count--;
            std::cout << "\r" << m_count << std::flush;
            if (ind->getScore() != 0 && (m_best == 0 || m_best < ind->getScore()))
            {
                m_best = ind->getScore();
                std::cout << "\r" << m_best << " " << ind->getFile() << std::endl;
            }
        }
    }
}
