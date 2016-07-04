
#include    "../GenLibTester/include/BrainView.hpp"
#include    "Test.hpp"

void        exec(Brain *brain)
{
    BrainView   view;

    while (1)
    {
        brain->exec();
        brain->make_skeleton();
        view.show_tester(brain);
        usleep(1000);
    }
}

void        prepareBrain(Brain *brain)
{
    SMART(GeneticalNode)        node(new GeneticalNode);
    ModuleClass                 *module;
    Decriptor                   *decr;
    std::pair<float, float>     pos;

    node->load_file("../neuronalTest/test.gen");
    pos.first = -80;
    pos.second = -60;
    for (unsigned int it = 0; it < 3; it++)
    {
        decr = new Decriptor(NULL);
        module = new ModuleClass(brain);
        module->attach_decriptor(decr);
        decr->set_block(node->get_son_ref(0)->copy());
        module->set_pos(pos);
        brain->add_object(module);
        pos.second += 60;
    }
    pos.first = 80;
    for (unsigned int it = 0; it < 3; it++)
    {
        pos.second -= 60;
        decr = new Decriptor(NULL);
        module = new ModuleClass(brain);
        module->attach_decriptor(decr);
        decr->set_block(node->get_son_ref(1)->copy());
        module->set_pos(pos);
        brain->add_object(module);
    }
}

int         main(int ac, char **av)
{
    Brain   *brain;
    SMART(GeneticalNode) dna;
    std::string   file;

    if (ac < 2)
      {
        std::cout << "./GenLibTester node_file" << std::endl;
        return (1);
      }
    file = av[1];
    srandom(time(NULL));

    brain = new Brain();
    dna = SMART(GeneticalNode)(new GeneticalNode());
    dna->load_file(file);
    brain->set_dna(dna);

    prepareBrain(brain);
    exec(brain);
    delete brain;
    return (0);
}
