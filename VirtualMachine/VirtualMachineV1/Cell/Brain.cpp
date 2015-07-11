
#include        "include/Cell/CellClass.hpp"
#include        "include/Cell/Brain.hpp"

Brain::Brain() : ModuleClass(0)
{
}

Brain::~Brain()
{

}

void        Brain::set_dna(GeneticalIndividu *node)
{
    SMART(CellClass)    cell;

    cell = SMART(CellClass)(new CellClass(this));
    cell->set_dna(node);
    add_object(cell);
}

void        Brain::exec()
{
    std::list<SMART(Object)>::iterator it;

    if (m_skel->get_begin() == m_skel->get_end())
        make_skeleton();
    for (it = m_obj.begin(); it != m_obj.end(); it++)
        (*it)->exec();
    make_move_line();
    move();
    catch_signals();
    make_skeleton();
}
