
#include        "GeneticalAlgo.hpp"

GeneticalAlgo::GeneticalAlgo(GeneticObj *parent) : GeneticObj(parent)
{
    m_size = 0;
    m_average = 0;
    m_best = 0;
}

GeneticalAlgo::~GeneticalAlgo()
{

}

void        GeneticalAlgo::set_size(int size)
{
    m_size = size;
}

void        GeneticalAlgo::set_engine(boost::shared_ptr<VirtualMachine> engine)
{
    m_engine = engine;
}

int         GeneticalAlgo::get_size()
{
    return (m_size);
}

double              GeneticalAlgo::get_best()
{
    return (m_best);
}

double              GeneticalAlgo::get_average()
{
    return (m_average);
}

void        GeneticalAlgo::move_population(std::list<SMART(ObjClass)> &to)
{
    to.insert(to.end(), m_son.begin(), m_son.end());
    m_son.clear();
}

void        GeneticalAlgo::add_individu(SMART(GeneticalIndividu) ind)
{
    m_son.push_back(ind);
}

void        GeneticalAlgo::save(std::ofstream &file)
{
    std::list<SMART(ObjClass)>::iterator it;

    if (!m_parent)
        GeneticObj::save(file);
    file << m_size << " ";
    file << m_son.size() << std::endl;
    for (it = m_son.begin(); it != m_son.end(); it++)
    {
        (*it)->save(file);
        file << std::endl;
    }
}

void        GeneticalAlgo::load(std::ifstream &file)
{
    int     size;

    if (!m_parent)
        GeneticObj::load(file);
    file >> m_size;
    file >> size;
    for (int it = 0; it < size; it++)
    {
        m_son.push_back(SMART(GeneticalIndividu)(new GeneticalIndividu(this)));
        m_son.back()->load(file);
    }
}
