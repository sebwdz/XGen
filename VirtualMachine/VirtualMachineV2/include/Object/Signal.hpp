#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include    <boost/unordered_map.hpp>
#include    <Object/Object.hpp>

#define     SIG_CATCH       void (SignalManager::*)(unsigned int, void*)

class       SignalManager : public Object
{
public:
    SignalManager(Object *parent);
    virtual ~SignalManager();

    void            add_signal(unsigned int value, void *ptr);
    virtual void    catch_signals() = 0;

    virtual void    catch_create(unsigned int code, void *sig);
    virtual void    catch_simple(unsigned int code, void *sig) = 0;
    virtual void    catch_duplic(unsigned int, void *sig) = 0;

protected:

    boost::unordered_map<unsigned int, SIG_CATCH> m_sig;
};

#endif // SIGNAL_HPP
