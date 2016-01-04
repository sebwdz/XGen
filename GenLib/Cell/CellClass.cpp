
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

void        CellClass::set_dna(SMART(GeneticalNode) dna)
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
  unsigned int        it;
  std::vector<SMART(GeneticalNode)> &vct = ((GeneticalNode*)sig)->get_son();

  (void)code;
  if (m_parent)
    {
      cell = new CellClass(m_parent);
      cell->set_dna(m_dna->copy());
      cell->set_pos(m_pos);
      cell->get_line()->shared_to_line(get_line());
      CAST(ModuleClass*)(m_parent)->add_object(cell);
      for (it = 0; it < vct.size(); it++)
        {
          decript = new Decriptor(NULL);
          decript->set_block(vct[it]->copy());
          decript->get_line()->shared_to_line(get_line());
          decript->set_pos(get_pos());
          cell->attach_decriptor(decript);
        }
    }
}
