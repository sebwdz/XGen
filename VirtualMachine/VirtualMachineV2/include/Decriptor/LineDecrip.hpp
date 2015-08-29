#ifndef LINEDECRIP_HPP
#define LINEDECRIP_HPP


#include    <boost/unordered_map.hpp>
#include    <Genetic/GeneticalIndividual.hpp>

#include    "chanel.hpp"
#include    "ChanelPropriety.hpp"
#include    "Opt.hpp"

#define     USE_LIST        boost::unordered_map<unsigned int, Chanel*>
#define     SIGNALS_LIST    boost::unordered_map<unsigned int, std::list<void*> >

class               LineDecript
{
public:

    LineDecript();
    ~LineDecript();

    void                    get_ready();
    Chanel                  *get_chan(unsigned int ref);
    ChanPropriety           *get_prop(unsigned int ref);
    void                    add_signal(unsigned int value, void *ptr);
    std::list<void*>        &get_signal(unsigned int signal);
    void                    shared_to_line(LineDecript *line);
    USE_LIST::iterator      get_begin();
    USE_LIST::iterator      get_end();
    CHANPLIST::iterator     get_begin_prop();
    CHANPLIST::iterator     get_end_prop();

private:

    USE_LIST                m_chan;
    SIGNALS_LIST            m_signals;
    CHANPLIST               m_prop;
};

#endif // LINEDECRIP_HPP
