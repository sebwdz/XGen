
#include        "include/Cell/CellClass.hpp"
#include        "include/Cell/Brain.hpp"

Brain::Brain() : ModuleClass(NULL)
{
  m_type ^= TYPE_BRAIN;
}

Brain::~Brain()
{

}

void        Brain::set_dna(boost::shared_ptr<GeneticalNode> block)
{
  CellClass       *cell;
  std::pair<float, float>   p;

  cell = new CellClass(this);
  cell->set_dna(block);
  p.first = 10;
  p.second = 20;
  cell->set_pos(p);
  add_object(cell);
}

void        Brain::exec()
{

  ModuleClass::exec();
  make_move_line();
  move();
  exec_move();
}
