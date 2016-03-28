
#include    "Test.hpp"

void        exec(Brain *brain)
{
    std::vector<Test*>  tests;
    unsigned int    it;
    CellClass       *cell;
    int             ok;
    unsigned int     diff;
    SMART(GeneticalNode)    input;
    SMART(GeneticalNode)    output;
    SMART(GeneticalNode)    out;
    SMART(GeneticalNode)    good;
    SMART(GeneticalNode)    bad;
    SMART(GeneticalNode)    tmp;
    int                     wait;
    float                   val;
    int                     itest;

    tests.push_back(new Test({true, true}, {true}));
    tests.push_back(new Test({true, false}, {false}));
    tests.push_back(new Test({false, true}, {false}));
    tests.push_back(new Test({false, false}, {false}));
    it = 0;
    diff = 0;
    if (!(cell = dynamic_cast<CellClass*>(*brain->get_begin())))
        return ;
    input = cell->get_line()->get_chan(Chanel::hash("Input"));
    output = cell->get_line()->get_chan(Chanel::hash("Output"));
    good = cell->get_line()->get_chan(Chanel::hash("Dopamine"))->get_ass(Chanel::hash("_data"))->get_son_ref(0);
    bad = cell->get_line()->get_chan(Chanel::hash("Peptide"))->get_ass(Chanel::hash("_data"))->get_son_ref(0);
    ok = 0;
    wait = 1;
    itest = 0;
    val = 0;
    while (it++ < 50000)
    {
        tests[itest]->apply(input);
        brain->exec();
        if (output->get_ass(Chanel::hash("_data"))->get_son().size())
        {
            tmp = boost::static_pointer_cast<GeneticalNode>(output->get_ass(Chanel::hash("_data"))->get_son_ref(0)->get_ref());
            if (tmp->get_ass(Chanel::hash("Active"))->get_value()._f > 0)
                ok++;
        }
        if (it - diff > 100)
        {
            std::cout << ok << std::endl;
            diff = it;
            tests[itest]->print();
            if (tests[itest]->evaluate(ok))
            {
                if (good->get_ref())
                    boost::static_pointer_cast<GeneticalNode>(good->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 10;
                std::cout << "ok " << std::endl;
            }
            else
            {
                if (bad->get_ref())
                    boost::static_pointer_cast<GeneticalNode>(bad->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 10;
                std::cout << "\t\t\tko " << std::endl;
            }
            ok = 0;
            if (val++ > 4)
            {
                for (unsigned int clean = 0; clean < 20; clean++)
                {
                    tests[itest]->apply(input);
                    brain->exec();
                }
                if (++itest >= tests.size())
                    itest = 0;
                val = 0;
            }
        }
        usleep(100);
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

    exec(brain);
    delete brain;
    return (0);
}
