#ifndef XGENFUNCTION_HPP
#define XGENFUNCTION_HPP

#include                    "XGenPackage.hpp"

class                       XGenFunction : public XGenPackage
{
public:
    void                    set_node(SMART(GeneticalNode) node) {m_node = node; m_node->set_type(VALUE);}

    SMART(GeneticalNode)    call(Decriptor *d, GeneticalNode*, SMART(GeneticalNode) av);

private:
    SMART(GeneticalNode)    m_node;
};

#endif // XGENFUNCTION_HPP
