
#include        <cmath>
#include        "Tester.hpp"

Tester::Tester() : MachineTester()
{
    m_view = 0;
}

Tester::~Tester()
{

}

void            Tester::set_individu(GeneticalIndividu *ind)
{
    SMART(Decriptor)    decript;
    GeneticalNode       *node;
    std::string         str("../../2Brain/test/out.gen");
    std::pair<float, float> pos(0, 100.0f);

    node = new GeneticalNode();
    node->load_file(str);
    m_brain = SMART(Brain)(new Brain());
    m_brain->set_dna(ind);
    m_ind = ind;
    for (int it = 0; it < 3; it++)
    {
        pos.second = (it * 65) - 75;
        pos.first = it == 1 ? 65 : 65;
        add_module(node, pos, true);
        pos.first = it == 1 ? -65 : -65;
        add_module(node, pos, false);
    }
}

void                                Tester::add_module(GeneticalNode *node, std::pair<float, float> &pos, bool sensor)
{
    SMART(Decriptor)                decript;
    SMART(ModuleClass)              module;
    std::string                     str("WHO");

    module = SMART(ModuleClass)(new ModuleClass());
    decript = SMART(Decriptor)(new Decriptor(module.get()));
    decript->set_node(node);
    module->add_object(decript);
    module->set_parent(m_brain.get());
    module->set_pos(pos);
    module->get_line()->get_chan(CHANNEL_RANGE + Chanel::hash(str))->set_value(sensor ? 0 : 0);
    m_brain->add_object(module);
}

void            Tester::set_view(MachineView *view)
{
    m_view = view;
}

void            Tester::exec()
{
    int      cycle;

    if (m_view)
        m_view->lock();
    cycle = 0;
    while (cycle < 500)
    {
        m_brain->exec();
        cycle += 1;
        if (m_view && !(cycle % 5))
            m_view->show_tester(this);
    }
    if (m_view)
        m_view->unlock();
}

Brain                               *Tester::get_brain()
{
    return (m_brain.get());
}
