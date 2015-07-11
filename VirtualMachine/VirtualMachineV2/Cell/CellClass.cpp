
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/CellClass.hpp"

CellClass::CellClass(Object *parent) : ModuleClass(parent)
{
    m_dna = 0;
    m_sig.insert(std::make_pair(DUPLIC, &SignalManager::catch_duplic));
}

CellClass::~CellClass()
{
}

void        CellClass::set_dna(GeneticalNode *dna)
{
    m_decript = SMART(Decriptor)(new Decriptor(this));
    m_decript->set_node(dna);   
    m_dna = dna;
}

void        CellClass::exec()
{
    m_decript->exec();
    ModuleClass::exec();
}

void        CellClass::catch_duplic(unsigned int code, void *sig)
{
    SMART(CellClass)   cell;

    (void)code;
    (void)sig;
    if (m_parent && CAST(ModuleClass*)(m_parent) && m_obj.size() < 20)
    {
        cell = SMART(CellClass)(new CellClass(m_parent));
        cell->set_dna(m_dna);
        cell->set_pos(m_pos);
        CAST(ModuleClass*)(m_parent)->add_object(cell);
    }
}
