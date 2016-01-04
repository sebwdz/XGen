#ifndef         CELL_CLASS_HPP_
#define         CELL_CLASS_HPP_

#include        "Decriptor/Decriptor.hpp"
#include        "Cell/Module.hpp"

class           CellClass : public ModuleClass
{
public:
    CellClass(Object *parent);
    ~CellClass();

    void                set_dna(SMART(GeneticalNode) dna);

    virtual void        exec();
    virtual void        catch_duplic(unsigned int, void *sig);


private:
    SMART(Decriptor)        m_decript;
    SMART(GeneticalNode)    m_dna;
};

#endif // CELL_CLASS_HPP_
