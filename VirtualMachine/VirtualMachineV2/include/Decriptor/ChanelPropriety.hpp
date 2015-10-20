#ifndef CHANELPROPRIETY_HPP
#define CHANELPROPRIETY_HPP

#include        <boost/unordered_map.hpp>
#include        "chanel.hpp"

#define         CHANPLIST       boost::unordered_map<unsigned int, ChanPropriety*>

class               ChanPropriety
{
public:
    ChanPropriety();
    ~ChanPropriety();

    void            set_ref(unsigned int ref);
    void            set_type(unsigned int type);
    void            set_pow(unsigned int type, float value);
    void            set_act(unsigned int type, unsigned int chan);
    void            set_chan(Chanel *chan);

    unsigned int    get_ref();
    bool            get_type(unsigned int type);
    unsigned int    *get_act();
    float           get_pow(unsigned int type);
    Chanel          *get_chan();
private:
    unsigned int    m_ref;
    bool            m_type;
    bool            m_dir;
    bool            m_atr;
    bool            m_attach;
    bool            m_link;
    float           m_dist;
    float           m_pow;
    unsigned int    m_act[2];
    Chanel          *m_chan;
};

#endif // CHANELPROPRIETY_HPP
