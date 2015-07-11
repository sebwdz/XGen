
#include        <cstdlib>
#include        "GeneticalIndividual.hpp"

GeneticalIndividu::GeneticalIndividu(GeneticObj *parent) : GeneticalNode(parent)
{
    m_fitness = 0;
}

GeneticalIndividu::~GeneticalIndividu()
{

}

SMART(ObjClass)     GeneticalIndividu::copy(SMART(ObjClass) cp)
{
    if (!cp)
        cp = SMART(GeneticalIndividu)(new GeneticalIndividu());
    return (GeneticalNode::copy(cp));
}

void        GeneticalIndividu::set_fitness(double fitness)
{
    m_fitness = fitness;
}

double      GeneticalIndividu::get_fitness()
{
    return (m_fitness);
}
