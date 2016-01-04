#ifndef LINEDECRIP_HPP
#define LINEDECRIP_HPP


#include    <boost/unordered_map.hpp>
#include    <Genetic/GeneticalNode.hpp>

#include    "chanel.hpp"
#include    "ChanelPropriety.hpp"
#include    "Opt.hpp"

#define     SIGNALS_LIST    std::vector<std::pair<unsigned int, void* > >

class               LineDecript
{
public:

    LineDecript();
    ~LineDecript();

    void                    get_ready();
    SMART(GeneticalNode)    get_chan(unsigned int key);
    SMART(GeneticalNode)    get_chan(GeneticalNode *node);
    SMART(GeneticalNode)    get_chan();
    SMART(GeneticalNode)    get_interaction();
    SMART(GeneticalNode)    get_shared();
    float                   get_value(unsigned int ref, bool use = false);
    void                    add_signal(unsigned int value, void *ptr);
    SIGNALS_LIST            &get_signals();
    void                    shared_to_line(LineDecript *line);
    USE_LIST::iterator      get_begin();
    USE_LIST::iterator      get_end();

private:

    SMART(GeneticalNode)    m_global;
    SMART(GeneticalNode)    m_shared;
    SIGNALS_LIST            m_signals;
    SMART(GeneticalNode)    m_prop;
};

#endif // LINEDECRIP_HPP
