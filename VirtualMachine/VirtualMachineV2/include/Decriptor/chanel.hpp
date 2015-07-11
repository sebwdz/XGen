#ifndef CHANEL_HPP
#define CHANEL_HPP

#include        <iostream>
#include        <list>

class       Chanel
{
public:
    Chanel();
    ~Chanel();

    static unsigned int             hash(std::string str);

    void                            set_ref(unsigned int ref);
    void                            set_wgth(unsigned int wgth);
    void                            set_use(bool use);
    void                            set_value(float value);
    void                            set_shared(bool shared);

    bool                            get_use();
    float                           get_value();
    unsigned int                    get_ref();
    unsigned int                    get_wgth();
    bool                            get_shared();

private:
    unsigned int                    m_ref;
    unsigned int                    m_wgth;
    bool                            m_use;
    float                           m_value;
    bool                            m_shared;
};

#endif // CHANEL_HPP
