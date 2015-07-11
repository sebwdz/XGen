#ifndef LINK_HPP_INCLUDED
#define LINK_HPP_INCLUDED

#include        "module.h"

class       Link : public ModuleClass
{
public:
        Link();
        ~Link();

private:
    ModuleClass     *to;
    double          m_len;
};

#endif // LINK_HPP_INCLUDED
