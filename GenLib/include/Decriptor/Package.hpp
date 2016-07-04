#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include                    <string>
#include                    "Decriptor.hpp"

class                       Package
{
public:
    virtual ~Package() { }
    virtual void            load(std::string const&) {}
    virtual void            add_package(unsigned int x, Package* p) { m_list[x] = p; }
    virtual Package         *getPackage(unsigned int x) const {return (m_list.at(x));}
    std::map<unsigned int, Package*> const      &getListe() const {
        return (m_list);
    }
private:
    std::map<unsigned int, Package*>    m_list;
};

class                       Function : public Package
{
public:
    virtual ~Function() { }
    virtual SMART(GeneticalNode)    call(Decriptor *d, GeneticalNode*, SMART(GeneticalNode)) = 0;
};

#endif // PACKAGE_HPP
