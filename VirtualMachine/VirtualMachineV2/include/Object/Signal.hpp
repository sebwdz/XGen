#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include    <boost/unordered_map.hpp>
#include    "Object/ObjectMap.hpp"

#define     SIG_CATCH       void (SignalManager::*)(unsigned int, void*)

class       SignalManager : public ObjectMap
{
public:
    SignalManager(Object *parent);
    virtual ~SignalManager();

    void            add_signal(unsigned int value, void *ptr);
    virtual void    catch_signals();

    virtual void    catch_create(unsigned int code, void *sig);
    virtual void    catch_simple(unsigned int code, void *sig);
    virtual void    catch_duplic(unsigned int, void *sig) = 0;

protected:

    boost::unordered_map<unsigned int, SIG_CATCH> m_sig;
};

#endif // SIGNAL_HPP
