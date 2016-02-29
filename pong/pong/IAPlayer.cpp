
#include                        <iostream>
#include                        "Cell/Module.hpp"
#include                        "Decriptor/Decriptor.hpp"
#include                        "include/IA.hpp"
#include                        "Decriptor/chanel.hpp"
#include                        "include/Ball.hpp"

IAPlayer::IAPlayer(std::string const& name) : Player()
{
    SMART(GeneticalNode)        node(new GeneticalNode());
    SMART(GeneticalNode)        sensor(new GeneticalNode());
    SMART(GeneticalNode)        actor(new GeneticalNode());

    sensor->load_file("../sensor.gen");
    actor->load_file("../actor.gen");
    node->load_file(name);
    m_brain = new Brain();
    m_brain->set_dna(node);

    for (unsigned int it = 0; it < 2; it++)
        m_brain->add_object(make_actor(it, actor));
    for (unsigned int it = 0; it < 2; it++)
        m_brain->add_object(make_sensor(it, sensor));

    std::cout << "New PONG_IA from file => " << name << std::endl;
    m_name = "PONG IA";
    m_type = Player::IA;
    m_view.setActive(false);

}

IAPlayer::~IAPlayer()
{

}

Object                          *IAPlayer::make_actor(unsigned int it, SMART(GeneticalNode) code)
{
    Decriptor                   *decript = new Decriptor(NULL);
    ModuleClass                 *module = new ModuleClass();
    std::pair<float, float>     pos;

    decript->set_block(code->copy());
    pos.first = -90;
    pos.second = 40 - (it * 80.0);
    module->set_pos(pos);
    module->attach_decriptor(decript);
    m_actor.push_back(module);
    return (module);
}

Object                          *IAPlayer::make_sensor(unsigned int it, SMART(GeneticalNode) code)
{
    Decriptor                   *decript = new Decriptor(NULL);
    ModuleClass                 *module = new ModuleClass();

    std::pair<float, float>     pos;
    decript->set_block(code->copy());
    pos.first = 70.0;
    pos.second = 50.0 - (it * 100.0);
    module->set_pos(pos);
    module->attach_decriptor(decript);
    m_sensor.push_back(module);
    return (module);
}

void                            IAPlayer::show()
{
    boost::mutex::scoped_try_lock   lock(m_mutex);

    while (!lock)
        lock = boost::mutex::scoped_try_lock(m_mutex);
    m_view.show_tester(m_brain);
}

void                            IAPlayer::UpdateView()
{
   float                        diff;
   unsigned int                chan = Chanel::hash("Impulse");

    if (!m_ball)
        return ;
    diff = m_pos.second - m_ball->get_pos().second;

    if (diff < 30 && diff > -30)
        diff = 0;
    if (diff != 0)
    {
        if (diff > 0)
            m_sensor[0]->get_line()->get_chan(chan)->get_value()._f = 10;
        else
            m_sensor[1]->get_line()->get_chan(chan)->get_value()._f = 10;
    }
}

void                            IAPlayer::exec()
{
    unsigned int                chan = Chanel::hash("Impulse");

    while (1)
    {
        boost::mutex::scoped_try_lock   lock(m_mutex);

        if (lock)
        {
            m_brain->exec();
            m_brain->make_skeleton();
            move(m_actor[1]->get_line()->get_chan(chan)->get_value()._f / 10);
            move(-m_actor[0]->get_line()->get_chan(chan)->get_value()._f / 10);
            UpdateView();
        }
    }
}
