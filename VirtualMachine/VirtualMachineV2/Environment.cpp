
#include            "Decriptor/Decriptor.hpp"
#include            "Environment.hpp"

Environment::Environment() : MachineTester()
{
    m_food = 0;
    m_dir = 0;
}

Environment::~Environment()
{

}

float           Environment::get_food()
{
    return (m_food);
}

void            Environment::init()
{
    int         cas;

    for (int x = 0; x < 20; x++)
    {
        for (int y = 0; y < 20; y++)
        {
            cas = rand() % 100;
            if (cas > 80)
                cas = FOOD;
            else
                cas = VOID;
            m_map.insert(std::make_pair(std::make_pair(x, y), cas));
        }
    }
}

void        Environment::set_brain(Brain *brain)
{
    m_brain = brain;
    m_pos.first = 10;
    m_pos.second = 10;
    m_map[m_pos] = CELL;
}

Brain       *Environment::get_brain()
{
    return (m_brain);
}

void        Environment::show(sf::RenderWindow  *win)
{
    boost::unordered_map<std::pair<int, int>, int>::iterator    it;
    //sf::Shape                                       blk;
    sf::CircleShape                                   blk;
    sf::Color                                       cl;
    std::pair<float, float>                         move;

    for (it = m_map.begin(); it != m_map.end(); it++)
    {
        if (it->second)
        {
            if (it->second == FOOD)
               cl = sf::Color(255, 0, 0);
            else
                cl = sf::Color(0, 0, 255);
            //blk = sf::Shape::Circle(20 + it->first.first * 20, 20 + it->first.second * 20, 10, cl);
            blk = sf::CircleShape(10);
            blk.setFillColor(cl);
            blk.move(it->first.first * 20, it->first.second * 20);
            //win->Draw(blk);
            win->draw(blk);
        }
    }
    cl.r = 0;
    cl.a = 175;
    cl.g = 100;
    cl.b = 0;/*
    std::pair<float, float> val;
    std::pair<float, float> tmp;
    for (int it = 0; it < 3; it++)
    {
        for (int v = -(it + 1); v <= (it + 1); v++)
        {
            val.first = (0 != 0 ? (it + 1) * (0) : v);
            val.second = (1 != 0 ? (it + 1) * (1) : v);
            tmp.first =  (int)(m_pos.first + (val.first * cos(m_dir * 3.14 / 180) + (-val.second * sin(m_dir * 3.14 / 180))));
            tmp.second = (int)(m_pos.second + (val.second * cos(m_dir * 3.14 / 180) + val.first * sin(m_dir * 3.14 / 180)));
            tmp.first = tmp.first > 0 ? (int)tmp.first % 20 : 20 - (int)tmp.first % 20;
            tmp.second = tmp.second > 0 ? (int)tmp.second % 20 : 20 - (int)tmp.second % 20;
            //blk = sf::Shape::Circle(20 + tmp.first * 20, 20 + tmp.second * 20, 10, cl);
            blk = sf::CircleShape(20);
            //win->Draw(blk);
            win->draw(blk);
        }
    }*/
}

void        Environment::exec()
{
    std::pair<float, float>     move;
    float                       tmp;
    std::string                 str("RES");
    std::string                 str2("GOOD");

    tmp = m_act[1]->get_line()->get_chan(Chanel::hash(str) + CHANNEL_RANGE)->get_value() / 10;
    m_dir -= m_act[0]->get_line()->get_chan(Chanel::hash(str) + CHANNEL_RANGE)->get_value();
    m_dir += m_act[2]->get_line()->get_chan(Chanel::hash(str) + CHANNEL_RANGE)->get_value();
    m_act[0]->get_line()->get_chan(Chanel::hash(str) + CHANNEL_RANGE)->set_value(0);
    m_act[1]->get_line()->get_chan(Chanel::hash(str) + CHANNEL_RANGE)->set_value(0);
    m_act[2]->get_line()->get_chan(Chanel::hash(str) + CHANNEL_RANGE)->set_value(0);
    move.first = -tmp * sin(m_dir * 3.14 / 180);
    move.second = cos(m_dir * 3.14 / 180) * tmp;
    m_map[m_pos] = VOID;
    m_pos.first += move.first;
    m_pos.second += move.second;
    m_pos.first = m_pos.first > 0 ? m_pos.first > 20 ? (int)m_pos.first % 20 : m_pos.first : 20 - (int)m_pos.first % 20;
    m_pos.second = m_pos.second > 0 ? m_pos.second > 20 ? (int)m_pos.second % 20 : m_pos.second : 20 - (int)m_pos.second % 20;
    if (m_map[m_pos] == FOOD)
        m_food += 1;
    m_map[m_pos] = CELL;
    for (int it = 0; it < (int)m_sensor.size(); it++)
    {
        move.first = it == 0 ? -1 : it == 2 ? 1 : 0;
        move.second = it == 1 ? 1 : 0;
        m_sensor[it]->get_line()->get_chan(Chanel::hash(str) + CHANNEL_RANGE)->set_value(get_sensor(m_pos, move));
        m_act[it]->get_line()->get_chan(Chanel::hash(str2) + CHANNEL_RANGE)->set_value(get_sensor(m_pos, move));
    }
}

void                                Environment::add_module(GeneticalNode *node, std::pair<float, float> &pos, bool sensor)
{
    SMART(Decriptor)                decript;
    SMART(ModuleClass)              module;
    std::string                     str("WHO");

    module = SMART(ModuleClass)(new ModuleClass());
    decript = SMART(Decriptor)(new Decriptor(module.get()));
    decript->set_node(node);
    module->add_object(decript);
    module->set_parent(m_brain);
    module->set_pos(pos);
    module->get_line()->get_chan(CHANNEL_RANGE + Chanel::hash(str))->set_value(sensor ? 0 : 30);
    m_brain->add_object(module);
    if (sensor)
        m_sensor.push_back(module);
    else
        m_act.push_back(module);
}

float            Environment::get_sensor(std::pair<float, float> pos, std::pair<float, float> vct)
{
    float                       res;
    std::pair<int, int>         tmp;
    std::pair<float, float>         val;

    res = 0;
    for (int it = 0; it < 4; it++)
    {
        for (int v = -(it + 1); v <= (it + 1); v++)
        {
            val.first = (vct.first != 0 ? (it + 1) * (vct.first) : v);
            val.second = (vct.second != 0 ? (it + 1) * (vct.second) : v);
            tmp.first =  (int)(pos.first + val.first * cos(m_dir * 3.14 / 180) + (-val.second * sin(m_dir * 3.14 / 180)));
            tmp.second = (int)(pos.second + cos(m_dir * 3.14 / 180) * val.second + val.first * sin(m_dir * 3.14 / 180));
            tmp.first = tmp.first > 0 ? tmp.first % 20 : 20 - tmp.first % 20;
            tmp.second = tmp.second > 0 ? tmp.second % 20 : 20 - tmp.second % 20;
            if (m_map[tmp] == FOOD)
                res += 5.0 - 1.0/(1.0 + exp(-it));
        }
    }
    return (res);
}
