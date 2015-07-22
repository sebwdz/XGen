
#include        <cmath>
#include        "Tester.hpp"

Tester::Tester()
{
    m_view = 0;
    m_env = new Environment();
    m_env->init();
}

Tester::~Tester()
{
    delete m_env;
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
    m_env->set_brain(m_brain.get());
    for (int it = 0; it < 3; it++)
    {
        pos.second = (it * 65) - 75;
        pos.first = it == 1 ? 65 : 65;
        m_env->add_module(node, pos, true);
        pos.first = it == 1 ? -65 : -65;
        m_env->add_module(node, pos, false);
    }
}

void            Tester::set_view(MachineView *view)
{
    m_view = view;
}

void            Tester::exec()
{
    float      fitness;
    int      cycle;

    fitness = 0;
    if (m_view)
        m_view->lock();
    cycle = 0;
    while (cycle < 500)
    {
        m_brain->exec();
        m_env->exec();
        cycle += 1;
        if (m_view && !(cycle % 5))
            m_view->show_tester(m_env);
    }
    if (m_view)
        m_view->unlock();
    fitness = m_env->get_food();
    if (fitness < 0)
        fitness = 0;
    if (fitness > 1000)
        fitness = 1000;
    std::cout << fitness << std::endl;
    m_ind->set_fitness(fitness);
}
