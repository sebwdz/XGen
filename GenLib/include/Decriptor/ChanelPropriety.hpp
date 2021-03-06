#ifndef CHANELPROPRIETY_HPP
#define CHANELPROPRIETY_HPP

#include        <boost/unordered_map.hpp>
#include        "Genetic/GeneticalNode.hpp"

#define         CHANPLIST       boost::unordered_map<unsigned int, ChanPropriety*>

class               ChanPropriety
{
public:
    ChanPropriety();
    ~ChanPropriety();

    void            set_ref(unsigned int ref);
    void            set_type(unsigned int type);
    void            set_pow(unsigned int type, float value);
    void            set_act(unsigned int type, SMART(GeneticalNode));
    void            set_chan(SMART(GeneticObj) chan);
    void            set_res(float res);

    unsigned int    get_ref() const;
    bool            get_type(unsigned int type) const;
    boost::shared_ptr<GeneticalNode> *get_act();
    float           get_pow(unsigned int type) const;
    boost::shared_ptr<GeneticObj> get_chan() const;
    float           get_res() const;

private:
    unsigned int      m_ref;
    bool              m_type;
    bool              m_dir;
    bool              m_atr;
    bool              m_attach;
    bool              m_link;
    bool              m_comin;
    float             m_dist;
    float             m_mindst;
    float             m_pow;
    SMART(GeneticalNode)      m_act[2];
    SMART(GeneticObj) m_chan;
    float             m_res;
};

#endif // CHANELPROPRIETY_HPP
