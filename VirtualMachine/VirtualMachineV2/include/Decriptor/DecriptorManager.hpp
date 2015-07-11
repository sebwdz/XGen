#ifndef DECRIPTORMANAGER_HPP
#define DECRIPTORMANAGER_HPP

#include        <boost/unordered_map.hpp>
#include        "Decriptor.hpp"

class           DecriptorManager
{
public:
    ~DecriptorManager();

    static DecriptorManager                    *get_instance();
    int     (Decriptor::*get_function(GeneticalNode*))(GeneticalNode*);

private:

    DecriptorManager();
    boost::unordered_map<int, int (Decriptor::*)(GeneticalNode*)>     m_opt;
};

#endif // DECRIPTORMANAGER_HPP
