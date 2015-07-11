
#include            <boost/functional/hash.hpp>
#include            "Decriptor/chanel.hpp"

Chanel::Chanel()
{
    m_value = 0;
    m_use = true;
    m_wgth = 0;
    m_ref = 0;
    m_shared = false;
}

Chanel::~Chanel()
{
}

unsigned int    Chanel::hash(std::string str)
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
    if (value < 0)
        value = 0;
    if (m_use)
        m_value = value;
}

void        Chanel::set_use(bool use)
{
    m_use = use;
    if (!m_use)
        m_value = 0;
}

void        Chanel::set_shared(bool shared)
{
    m_shared = shared;
}

bool        Chanel::get_use()
{
    return (m_use);
}

float       Chanel::get_value()
{
    return (m_value);
}

unsigned int    Chanel::get_ref()
{
    return (m_ref);
}

unsigned int    Chanel::get_wgth()
{
    return (m_wgth);
}

bool            Chanel::get_shared()
{
    return (m_shared);
}
