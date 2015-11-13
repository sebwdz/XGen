#ifndef CHANEL_HPP
#define CHANEL_HPP

#include        <iostream>
#include        <list>
#include        "Monitor.hpp"

class       Chanel
{
public:
    Chanel();
    ~Chanel();

    static unsigned int             hash(std::string str);

    void                            set_ref(unsigned int ref);
    void                            set_use(bool use);
    void                            set_value(float value);
    void                            set_shared(bool shared);

    bool                            get_use() const;
    float                           get_value() const;
    unsigned int                    get_ref() const;
    bool                            get_shared() const;

private:
    unsigned int                    m_ref;
    bool                            m_use;
    float                           m_value;
    bool                            m_shared;
};

#endif // CHANEL_HPP
