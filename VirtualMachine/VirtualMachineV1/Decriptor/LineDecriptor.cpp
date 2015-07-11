
#include        "Decriptor/LineDecrip.hpp"

LineDecript::LineDecript()
{
}

LineDecript::~LineDecript()
{
    USE_LIST::iterator it;
    for (it = m_chan.begin(); it != m_chan.end(); it++)
        delete it->second;
}

void                LineDecript::get_ready()
{
    m_signals.clear();
}

void                LineDecript::add_signal(unsigned int value, void *ptr)
{
    SIGNALS_LIST::iterator it;

    it = m_signals.find(value);
    if (it == m_signals.end())
    {
        m_signals.insert(std::make_pair(value, std::list<void*>()));
        it = m_signals.find(value);
    }
    it->second.push_back(ptr);
}

std::list<void *> &LineDecript::get_signal(unsigned int signal)
{
    static std::list<void*> res;

    if (m_signals.find(signal) != m_signals.end())
        return (m_signals[signal]);
    return (res);
}

Chanel              *LineDecript::get_chan(unsigned int ref)
{
    USE_LIST::iterator  it;
    Chanel              *chan;

    if ((it = m_chan.find(ref)) == m_chan.end())
    {
        chan = new Chanel();
        chan->set_ref(ref);
        m_chan.insert(std::make_pair(ref, chan));
    }
    else
        chan = it->second;
    return (chan);
}

USE_LIST::iterator  LineDecript::get_begin()
{
    return (m_chan.begin());
}


USE_LIST::iterator  LineDecript::get_end()
{
    return (m_chan.end());
}
