
#include        <cmath>
#include        "Tester.hpp"

Tester::Tester() : MachineTester()
{
    m_view = 0;
}

Tester::~Tester()
{

}

void            Tester::set_individu(SMART(GeneticalIndividu) ind)
{
    SMART(Decriptor)    decript;
    GeneticalNode       *node;
    std::string         str("../../2Brain/test/out.gen");
    std::pair<float, float> pos(0, 100.0f);

    //node = new GeneticalNode();
    //node->load_file(str);
    m_brain = SMART(Brain)(new Brain());
    m_brain->set_dna(ind);
    m_ind = ind;
    return ;
    for (int it = 0; it < 3; it++)
    {
        pos.second = (it * 80) - 75;
        pos.first = it == 1 ? 75 : 75;
        add_module(node, pos, true);
        pos.first = it == 1 ? -75 : -75;
        add_module(node, pos, false);
    }
}

void                                Tester::add_module(GeneticalNode *node, std::pair<float, float> &pos, bool sensor)
{
    /*SMART(Decriptor)                decript;
    SMART(ModuleClass)              module;
    std::string                     str("WHO");

    module = SMART(ModuleClass)(new ModuleClass());
    decript = SMART(Decriptor)(new Decriptor(module.get()));
    decript->set_node(node);
    module->add_object(decript);
    module->set_parent(m_brain.get());
    module->set_pos(pos);
    module->get_line()->get_chan(CHANNEL_RANGE + Chanel::hash(str))->set_value(sensor ? 0 : 0);
    m_brain->add_object(module);*/
}

void            Tester::set_view(MachineView *view)
{
    m_view = view;
}

void            Tester::exec()
{
    int      cycle;
    int      average = 0;
    int      max = 0;
    int     all = 0;
    float   tall = 0;
    float   last = 0;
    float   prev[2] = {0};
    struct timeval      _time[2];
    struct timeval      _all[2];

    if (m_view)
        m_view->lock();
    cycle = 0;
    gettimeofday(&_time[0], NULL);
    gettimeofday(&_all[0], NULL);
    while (cycle < 1000)
    {
        if (m_view)
            m_brain->make_skeleton();
        m_brain->exec();
        cycle += 1;
        if (m_view && !(cycle % 5))
            m_view->show_tester(this);
        if (!(cycle % 30))
        {
            gettimeofday(&_time[1], NULL);
            average += 30.0 / (float)((_time[1].tv_sec + _time[1].tv_usec / 1000000.0) - (_time[0].tv_sec + _time[0].tv_usec / 1000000.0));
            last = 30.0 / (float)((_time[1].tv_sec + _time[1].tv_usec / 1000000.0) - (_time[0].tv_sec + _time[0].tv_usec / 1000000.0));
            tall += Monitor::get_instance()->get_time();
            prev[0] = Monitor::get_instance()->get_instru();
            prev[1] = Monitor::get_instance()->get_time();
            if (max < 30.0 / (float)((_time[1].tv_sec + _time[1].tv_usec / 1000000.0) - (_time[0].tv_sec + _time[0].tv_usec / 1000000.0)))
                max = 30.0 / (float)((_time[1].tv_sec + _time[1].tv_usec / 1000000.0) - (_time[0].tv_sec + _time[0].tv_usec / 1000000.0));
            all += Monitor::get_instance()->get_instru();
            Monitor::get_instance()->reset_instru();
            gettimeofday(&_time[0], NULL);
        }
    }
    gettimeofday(&_all[1], NULL);
    std::cout << "last " << last << " c/s   " << prev[0] / 30 << " instrs/c     " << ( prev[0] ) / ( prev[1] * 1000 ) << " * 10⁶ instrs/s" << std::endl;
    std::cout << "Average : " << average / (cycle / 30) << " c/s" << std::endl;
    std::cout << "Max : " << max  << " c/s" << std::endl;
    std::cout << all / 1000.0  << " * 10³ instrs" << std::endl;
    std::cout << "total time = " << ((float)((_all[1].tv_sec + _all[1].tv_usec / 1000000.0) - (_all[0].tv_sec + _all[0].tv_usec / 1000000.0))) << " s " << std::endl;
    std::cout << all / (((float)((_all[1].tv_sec + _all[1].tv_usec / 1000000.0) - (_all[0].tv_sec + _all[0].tv_usec / 1000000.0))) * 1000000 ) << " * 10⁶ instrs/s" << std::endl;
    std::cout << "time in instrs = " << tall / 1000 << " s " << std::endl;
    std::cout << all / (tall * 1000 ) << " * 10⁶ instrs/s" << std::endl;
    if (m_view)
        m_view->unlock();
}

Brain                               *Tester::get_brain()
{
    return (m_brain.get());
}
