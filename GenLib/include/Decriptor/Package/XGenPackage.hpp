#ifndef XGENPACKAGE_HPP
#define XGENPACKAGE_HPP

#include                    "Decriptor/Package.hpp"

typedef class XGenFunction  XGenFunction;

class                       XGenPackage : public Function
{
public:
    virtual SMART(GeneticalNode)    call(Decriptor*, GeneticalNode*, SMART(GeneticalNode)) {return (SMART(GeneticalNode)());}
    virtual void            load(std::string const& file);
    virtual void            load(GeneticalNode *node);

private:
};

#endif // XGENPACKAGE_HPP
