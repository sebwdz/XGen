
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

    tests.push_back(new Test({true, true}, {false}));
    tests.push_back(new Test({true, false}, {true}));
    tests.push_back(new Test({false, true}, {true}));
    tests.push_back(new Test({false, false}, {true}));
    it = 0;
    diff = 0;
    if (!(cell = dynamic_cast<CellClass*>(*brain->get_begin())))
        return ;
    for (unsigned int clean = 0; clean < 30; clean++)
        brain->exec();
    input = cell->get_line()->get_chan(Chanel::hash("Input"));
    output = cell->get_line()->get_chan(Chanel::hash("Output"));
    good = cell->get_line()->get_chan(Chanel::hash("Dopamine"))->get_ass(Chanel::hash("_data"))->get_son_ref(0);
    bad = cell->get_line()->get_chan(Chanel::hash("Peptide"))->get_ass(Chanel::hash("_data"))->get_son_ref(0);
    ok = 0;
    wait = 1;
    itest = 0;
    val = 0;
    it = 0;
    while (it++ < 100000)
    {
        tests[itest]->apply(input);
        brain->exec();
        /*if (output->get_ass(Chanel::hash("_data"))->get_son().size())
        {
            tmp = boost::static_pointer_cast<GeneticalNode>(output->get_ass(Chanel::hash("_data"))->get_son_ref(0)->get_ref());
            if (tmp->get_ass(Chanel::hash("Active"))->get_value()._f > 0)
                ok++;
        }*/
        if (it - diff > 50)
        {
            if (output->get_ass(Chanel::hash("_data"))->get_son().size())
                    {
                        tmp = boost::static_pointer_cast<GeneticalNode>(output->get_ass(Chanel::hash("_data"))->get_son_ref(0)->get_ref());
                        if (tmp->get_ass(Chanel::hash("Accu"))->get_value()._f > 3)
                            ok++;
                        std::cout << "accu => " << tmp->get_ass(Chanel::hash("Accu"))->get_value()._f << std::endl;
                    }
            if (it > 95000)
            {
                std::cout << "NO LEARN !" << std::endl;
            }
            std::cout << ok << std::endl;
            diff = it;
            tests[itest]->print();
            if (tests[itest]->evaluate(ok))
            {
                if (it < 95000 && good->get_ref())
                    boost::static_pointer_cast<GeneticalNode>(good->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
                std::cout << "ok " << std::endl;
            }
            else
            {
                if (it < 95000 && bad->get_ref())
                    boost::static_pointer_cast<GeneticalNode>(bad->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
                std::cout << "\t\t\t\t\t\tko " << std::endl;
            }
            ok = 0;
            if (val++ > 3)
            {
                for (unsigned int clean = 0; clean < 30; clean++)
                {
                    tests[itest]->apply(input);
                    brain->exec();
                }
                val = 0;
                if (++itest >= tests.size())
                {
                    std::cout << "######################## BEGIN SESSION ########################" << std::endl;
                    itest = 0;
                }
                for (unsigned int clean = 0; clean < 30; clean++)
                {
                    tests[itest]->apply(input);
                    brain->exec();
                }
            }
        }
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
