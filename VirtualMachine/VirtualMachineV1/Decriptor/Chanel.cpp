
#include            <boost/functional/hash.hpp>
#include            "Decriptor/chanel.hpp"

Chanel::Chanel()
{
    m_value = 0;
    m_use = true;
    m_wgth = 0;
    m_ref = 0;
}

Chanel::~Chanel()
{
    CHAN_P::iterator     it;

    for (it = m_atr.begin(); it != m_atr.end(); it++)
        delete *it;
}

unsigned int    Chanel::hash(std::string &str)
{
    unsigned int                res;
    boost::hash<std::string>    hsh;

    res = hsh(str);
    return (res % 3000000);
}

void        Chanel::set_ref(unsigned int ref)
{
    m_ref = ref;
}

void        Chanel::set_wgth(unsigned int wgth)
{
    m_wgth = wgth;
}

void        Chanel::set_value(float value)
{
    m_value = value;
}

void        Chanel::set_use(bool use)
{
    m_use = use;
}

chanPropriety   *Chanel::get_propriety(unsigned int ref, bool type, bool dir)
{
    chanPropriety                       *prop;
    CHAN_P::iterator                    it;

    for (it = m_atr.begin(); it != m_atr.end(); it++)
    {
        prop = *it;
        if (prop->m_type == type && prop->m_dir == dir && prop->m_ref == ref)
            return (prop);
    }
    prop = new chanPropriety;
    prop->m_dir = dir;
    prop->m_type = type;
    prop->m_ref = ref;
    prop->m_pow = 0;
    prop->m_dist = 0;
    m_atr.push_back(prop);
    return (prop);
}

CHAN_P::iterator                Chanel::get_begin()
{
    return (m_atr.begin());
}

CHAN_P::iterator                Chanel::get_end()
{
    return (m_atr.end());
}

bool                            Chanel::get_use()
{
    return (m_use);
}

float                           Chanel::get_value()
{
    return (m_value);
}

unsigned int                    Chanel::get_ref()
{
    return (m_ref);
}

unsigned int                    Chanel::get_wgth()
{
    return (m_wgth);
}
