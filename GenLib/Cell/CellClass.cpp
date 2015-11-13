
#include        "Decriptor/Decriptor.hpp"
#include        "Cell/CellClass.hpp"

CellClass::CellClass(Object *parent) : ModuleClass(parent)
{
  m_sig.insert(std::make_pair(DUPLIC, &SignalManager::catch_duplic));
  m_type ^= TYPE_CELL;
}

CellClass::~CellClass()
{
}

void        CellClass::set_dna(SMART(GeneticObj) dna)
{
  m_decript = SMART(Decriptor)(new Decriptor(this));
  m_decript->set_block(dna);
  m_decript->set_attach(true);
  m_dna = dna;
}

void        CellClass::exec()
{
  m_decript->exec();
  ModuleClass::exec();
}

void        CellClass::catch_duplic(unsigned int code, void *sig)
{
  CellClass           *cell;
  Decriptor           *decript;
  OBJ_IT              it;
  OBJ_IT              end;

  (void)code;
  if (m_parent)
    {
      cell = new CellClass(m_parent);
      cell->set_dna(boost::static_pointer_cast<GeneticObj>(m_dna->copy()));
      cell->set_pos(m_pos);
      cell->get_line()->shared_to_line(get_line());
      CAST(ModuleClass*)(m_parent)->add_object(cell);
      end = ((GeneticalNode*)sig)->get_son().end();
      for (it = ((GeneticalNode*)sig)->get_son().begin(); it != end; it++)
        {
          decript = new Decriptor(NULL);
          decript->set_block(boost::static_pointer_cast<GeneticObj>((*it)->copy()));
          decript->get_line()->shared_to_line(get_line());
          decript->set_pos(get_pos());
          cell->attach_decriptor(decript);
        }
    }
}
