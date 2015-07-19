
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
    SMART(Decriptor)   decript;
    OBJ_IT             it;

    (void)code;
    if (m_parent)
    {
        cell = SMART(CellClass)(new CellClass(m_parent));
        cell->set_dna(m_dna);
        cell->set_pos(m_pos);
        cell->get_line()->shared_to_line(get_line());
        CAST(ModuleClass*)(m_parent)->add_object(cell);
        for (it = ((GeneticalNode*)sig)->get_begin(); it != ((GeneticalNode*)sig)->get_end(); it++)
        {
            decript = SMART(Decriptor)(new Decriptor(NULL));
            decript->set_node(CAST(GeneticalNode*)(it->get()));
            decript->get_line()->shared_to_line(get_line());
            decript->set_pos(get_pos());
            cell->add_object(decript);
        }
    }
}
