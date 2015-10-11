
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
    m_signals.push_back(std::make_pair(value, ptr));
}

SIGNALS_LIST        &LineDecript::get_signals()
{
    return (m_signals);
}

 unsigned int            LineDecript::get_value(unsigned int ref, bool use)
 {
     USE_LIST::iterator it;
    if ((it = m_chan.find(ref)) == m_chan.end())
        return (use ? 1 : 0);
    if (!use)
        return (it->second->get_value());
    return (it->second->get_use() ? 1 : 0);
 }

void                    LineDecript::shared_to_line(LineDecript *line)
{
    USE_LIST::iterator  it;
    Chanel              *chan;

    for (it = line->get_begin(); it != line->get_end(); it++)
    {
        if (it->second->get_shared())
        {
            chan = get_chan(it->first);
            chan->set_use(it->second->get_use());
            chan->set_value(it->second->get_value());
        }
    }
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

ChanPropriety           *LineDecript::get_prop(unsigned int ref)
{
    CHANPLIST::iterator it;
    ChanPropriety       *prop;

    if ((it = m_prop.find(ref)) == m_prop.end())
    {
        prop = new ChanPropriety();
        prop->set_ref(ref);
        m_prop.insert(std::make_pair(ref, prop));
    }
    else
        prop = it->second;
    return (prop);
}

USE_LIST::iterator  LineDecript::get_begin()
{
    return (m_chan.begin());
}


USE_LIST::iterator  LineDecript::get_end()
{
    return (m_chan.end());
}

CHANPLIST::iterator LineDecript::get_begin_prop()
{
    return (m_prop.begin());
}

CHANPLIST::iterator LineDecript::get_end_prop()
{
    return (m_prop.end());
}
