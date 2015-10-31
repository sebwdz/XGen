#ifndef         CELL_CLASS_HPP_
#define         CELL_CLASS_HPP_

#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Module.hpp"

class           CellClass : public ModuleClass
{
public:
    CellClass(Object *parent);
    ~CellClass();

    void                set_dna(boost::shared_ptr<GeneticObj> dna);

    virtual void        exec();
    virtual void        catch_duplic(unsigned int, void *sig);


private:
    SMART(Decriptor)        m_decript;
    SMART(GeneticObj)       m_dna;
};

#endif // CELL_CLASS_HPP_
