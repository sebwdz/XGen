
#include        "GeneticalPool.hpp"

GeneticalPool::GeneticalPool(GeneticObj *parent) : GeneticalAlgo(parent)
{
    m_continue = true;
    m_start = false;
}

GeneticalPool::~GeneticalPool()
{

}

void        GeneticalPool::set_size(int size)
{
    m_size = size;
    for (int it = 0; it < (int)m_pool.size(); it++)
        m_pool[it]->set_size(size / m_pool.size());
}

void        GeneticalPool::set_pool_len(int len)
{
    m_poolLen = len;
}

void        GeneticalPool::set_pool_height(int height)
{
    m_height = height;
}

void        GeneticalPool::set_continue(bool cont)
{
    m_continue = cont;
    for (int it = 0; it < (int)m_pool.size(); it++)
        m_pool[it]->set_continue(cont);
}

void        GeneticalPool::set_propriety(boost::shared_ptr<GeneticPropriety> propriety)
{
    if (propriety)
        GeneticObj::set_propriety(propriety);
    for (int it = 0; it < (int)m_pool.size(); it++)
        m_pool[it]->set_propriety(m_propriety);
}

int         GeneticalPool::get_pool_len()
{
    return (m_poolLen);
}

int         GeneticalPool::get_pool_height()
{
    return (m_height);
}

bool        GeneticalPool::get_start()
{
    return (m_start);
}

void        GeneticalPool::set_engine(boost::shared_ptr<VirtualMachine> engine)
{
    GeneticalAlgo::set_engine(engine);
}

void    GeneticalPool::save(std::ofstream &file)
{
    file << m_pool.size() << " ";
    file << m_poolLen << " ";
    file << m_height << std::endl;
    GeneticalAlgo::save(file);
    for (int it = 0; it < (int)m_pool.size(); it++)
    {
        m_pool[it]->save(file);
    }
}

void    GeneticalPool::load(std::ifstream &file)
{
    int size;
    GeneticalPool   *son;

    file >> size;
    file >> m_poolLen;
    file >> m_height;
    GeneticalAlgo::load(file);
    for (int it = 0; it < size; it++)
    {
        m_pool.push_back(SMART(GeneticalPool)(new GeneticalPool(this)));
        son = m_pool.back().get();
        son->set_engine(m_engine);
        son->load(file);
    }
}
