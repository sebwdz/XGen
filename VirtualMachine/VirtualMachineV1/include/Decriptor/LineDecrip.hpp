#ifndef LINEDECRIP_HPP
#define LINEDECRIP_HPP

#define     USE_CHAN        0
#define     MOVE            1
#define     RESIST          2
#define     DECRIPT_SIZE    3

#include    <boost/unordered_map.hpp>
#include    <Genetic/GeneticalIndividual.hpp>

#define     USE_LIST        boost::unordered_map<unsigned int, Chanel*>
#define     SIGNALS_LIST    boost::unordered_map<unsigned int, std::list<void*> >

#include    "chanel.hpp"
#include    "Opt.hpp"

class               LineDecript
{
public:

    LineDecript();
    ~LineDecript();

    void                    get_ready();
    Chanel                  *get_chan(unsigned int ref);
    void                    add_signal(unsigned int value, void *ptr);
    std::list<void*>        &get_signal(unsigned int signal);
    USE_LIST::iterator      get_begin();
    USE_LIST::iterator      get_end();

private:

    USE_LIST                m_chan;
    SIGNALS_LIST            m_signals;
};

#endif // LINEDECRIP_HPP
