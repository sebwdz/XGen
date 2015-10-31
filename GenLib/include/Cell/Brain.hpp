#ifndef BRAIN_HPP
#define BRAIN_HPP

#include    <map>
#include    "Module.hpp"

class       Brain : public ModuleClass
{
public:
    Brain();
    virtual ~Brain();

    virtual void                    exec();
    void                            set_dna(SMART(GeneticObj) node);
};

#endif // BRAIN_HPP
