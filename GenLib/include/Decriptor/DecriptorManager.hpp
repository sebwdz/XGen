#ifndef DECRIPTORMANAGER_HPP
#define DECRIPTORMANAGER_HPP

#include        <boost/unordered_map.hpp>
#include        "Package.hpp"

typedef union   decriptFunction
{
    int (Decriptor::*fct)(GeneticalNode*);
    void              *ptr;
} decriptFunction;

class           DecriptorManager
{
public:
    ~DecriptorManager();

    void                                        load_packages();
    static DecriptorManager                     *get_instance();
    SMART(GeneticalNode)                        (Decriptor::*get_function(GeneticalNode*))(GeneticalNode*);
    Package                                     *get_package(unsigned int) const;

private:

    DecriptorManager();
    boost::unordered_map<int, SMART(GeneticalNode) (Decriptor::*)(GeneticalNode*)>     m_opt;
    Package                                                                            *m_package;
};

#endif // DECRIPTORMANAGER_HPP
