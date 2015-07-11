#ifndef CHANEL_HPP
#define CHANEL_HPP

#include        <iostream>
#include        <list>

#define         CHAN_P      std::list<chanPropriety*>

typedef struct  chanPropriety
{
    unsigned int    m_ref;
    bool            m_type;
    bool            m_dir;
    float           m_dist;
    float           m_pow;
}               chanPropriety;

class       Chanel
{
public:
    Chanel();
    ~Chanel();

    static unsigned int             hash(std::string &str);

    void                            set_ref(unsigned int ref);
    void                            set_wgth(unsigned int wgth);
    void                            set_use(bool use);
    void                            set_value(float value);

    bool                            get_use();
    float                           get_value();
    unsigned int                    get_ref();
    unsigned int                    get_wgth();

    chanPropriety                   *get_propriety(unsigned int ref, bool type, bool dir);
    CHAN_P::iterator                get_begin();
    CHAN_P::iterator                get_end();

private:
    unsigned int                    m_ref;
    unsigned int                    m_wgth;
    bool                            m_use;
    float                           m_value;
    CHAN_P                          m_atr;
};

#endif // CHANEL_HPP
