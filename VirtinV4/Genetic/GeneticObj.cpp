
#include        "Genetic/GeneticObj.hpp"

GeneticObj::GeneticObj(GeneticObj *parent) : ObjClass(parent)
{
    m_len = 0;
    if (parent)
        set_propriety(parent->get_propriety());
    else if (!m_propriety.get())
        m_propriety = SMART(GeneticPropriety)(new GeneticPropriety);
}

GeneticObj::~GeneticObj()
{
}

void    GeneticObj::set_propriety(boost::shared_ptr<GeneticPropriety> propriety)
{
    std::list<SMART(ObjClass)>::iterator it;

    if (propriety)
       m_propriety = propriety;
    for (it = m_son.begin(); it != m_son.end(); it++)
        CAST(GeneticObj*)((*it).get())->set_propriety(m_propriety);
}

boost::shared_ptr<GeneticPropriety> GeneticObj::get_propriety()
{
    return (m_propriety);
}

unsigned int        GeneticObj::get_alea_range()
{
    int             range;
    unsigned int    value;

    range = rand() % m_propriety->range.size();
    value = (rand() % (m_propriety->range[range].second -
                      m_propriety->range[range].first)) + m_propriety->range[range].first;
    return (value);
}

int                 GeneticObj::get_len()
{
    return (m_len);
}

bool        GeneticObj::alea(int range, int target)
{
    double  value;

    value = rand() % range;
    if (value > target)
        return (true);
    return (false);
}


void    GeneticObj::save(std::ofstream &file)
{
    file << m_propriety->len << " ";
    file << m_propriety->height << " ";
    file << m_propriety->range.size() << std::endl;
    for (int it = 0; it < (int)m_propriety->range.size(); it++)
    {
        file << m_propriety->range[it].first << " ";
        file << m_propriety->range[it].second << std::endl;
    }
}

void    GeneticObj::load(std::ifstream &file)
{
    int nb = 0;
    std::pair<std::string, unsigned int> p;

    file >> m_propriety->len;
    file >> m_propriety->height;
    file >> nb;
    for (int it = 0; it < nb; it++)
    {
        m_propriety->range.push_back(std::make_pair(0, 0));
        file >> m_propriety->range[it].first;
        file >> m_propriety->range[it].second;
    }
}
