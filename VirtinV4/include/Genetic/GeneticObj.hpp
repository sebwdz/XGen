#ifndef GENETICOBJ_HPP
#define GENETICOBJ_HPP

#include    <vector>
#include    <list>
#include    <obj.hpp>

#define        VAR_LIST                                 std::list<std::pair<std::string, unsigned int> >

class                   GeneticObj : public ObjClass
{
public:
    GeneticObj(GeneticObj *parent = 0);
    virtual ~GeneticObj();

    virtual void        save(std::ofstream &file) = 0;
    virtual void        load(std::ifstream &file) = 0;
protected:
};

#endif // GENETICOBJ_HPP
