
#include        "include/Cell/CellClass.hpp"
#include        "include/Cell/Brain.hpp"

Brain::Brain() : ModuleClass(NULL)
{
  m_type ^= TYPE_BRAIN;
}

Brain::~Brain()
{

}

void        Brain::set_dna(SMART(GeneticalNode) node)
{
    CellClass       *cell;

    cell = new CellClass(this);
    cell->set_dna(node);
    add_object(cell);
}

void        Brain::exec()
{
    unsigned int    it;

    SignalManager::catch_signals();
    for (it = 0; it < m_obj.size(); it++)
        m_obj[it]->exec();
    make_move_line();
    move();
    exec_move();
}
