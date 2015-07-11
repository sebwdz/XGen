#ifndef GENETICALINDIVIDUAL_HPP_INCLUDED
#define GENETICALINDIVIDUAL_HPP_INCLUDED

#include        "Genetic/GeneticalNode.hpp"

class           GeneticalIndividu : public GeneticalNode
{
public:
    GeneticalIndividu(GeneticObj *parent = 0);
    virtual ~GeneticalIndividu();

    SMART(ObjClass)     copy(SMART(ObjClass) cp = SMART(ObjClass)());

    void        set_fitness(double fitness);
    double      get_fitness();

private:
    double          m_fitness;
};


#endif // GENETICALINDIVIDUAL_HPP_INCLUDED
