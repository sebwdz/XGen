#ifndef DECRIPTORMANAGER_HPP
#define DECRIPTORMANAGER_HPP

#include        <boost/unordered_map.hpp>
#include        "Decriptor.hpp"

typedef union   decriptFunction
{
    int (Decriptor::*fct)(GeneticalNode*);
    void              *ptr;
} decriptFunction;

class           DecriptorManager
{
public:
    ~DecriptorManager();

    static DecriptorManager                    *get_instance();
    SMART(GeneticalNode)                       (Decriptor::*get_function(GeneticalNode*))(GeneticalNode*);

private:

    DecriptorManager();
    boost::unordered_map<int, SMART(GeneticalNode) (Decriptor::*)(GeneticalNode*)>     m_opt;
};

#endif // DECRIPTORMANAGER_HPP
