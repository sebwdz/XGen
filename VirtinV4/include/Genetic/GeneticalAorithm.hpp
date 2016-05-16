#ifndef GENETICALAORITHM_HPP
#define GENETICALAORITHM_HPP

#include        <boost/thread.hpp>
#include        "Genetic/Individu.hpp"

class GeneticAlgorithm
{
public:
    GeneticAlgorithm();
    ~GeneticAlgorithm();

    void                            generate(unsigned int);
    void                            setPatern(SMART(GeneticalNode));
    void                            exec(unsigned int size);
    void                            load();
    void                            evaluate();
    Individu                        *selection(Individu *prev = NULL);

    Individu                        *getNext();
    void                            threadWork();

private:
    SMART(GeneticalNode)            m_patern;
    std::vector<SMART(Individu)>    m_pop;
    float                           m_best;
    std::vector<Individu*>          m_work;
    std::vector<boost::thread*>     m_thread;
    float                           m_count;

    boost::mutex                    m_sleep;
    boost::condition_variable       m_var;
    boost::mutex                    m_lockwork;
};

#endif // GENETICALAORITHM_HPP
