
#include    <cmath>
#include    "Cell/Brain.hpp"
#include    "Cell/CellClass.hpp"
#include    "include/Snake.hpp"

Snake::Snake()
{
    srandom(time(NULL));
    CellClass               *cell;
    SMART(GeneticalNode)    node = SMART(GeneticalNode)(new GeneticalNode());

    node->load_file("../Snake/out.gen");
    m_brain.set_dna(node);

    for (unsigned int clean = 0; clean < 500; clean++)
        m_brain.exec();
    std::cout << "ready" << std::endl;

    cell = dynamic_cast<CellClass*>(*m_brain.get_begin());
    m_input = cell->get_line()->get_chan(Chanel::hash("Input"));
    m_output = cell->get_line()->get_chan(Chanel::hash("Output"));
    m_good = cell->get_line()->get_chan(Chanel::hash("Dopamine"))->get_ass(Chanel::hash("_data"))->get_son_ref(0);
    m_bad = cell->get_line()->get_chan(Chanel::hash("Peptide"))->get_ass(Chanel::hash("_data"))->get_son_ref(0);

    m_lastEat = 0;
    m_pos.first = 25;
    m_pos.second = 25;
    m_dir.first = 0;
    m_dir.second = 0;
    m_angle = 0;
    m_mv = 0;
}

std::pair<float, float>     const   &Snake::getPos() const
{
    return (m_pos);
}

float                               Snake::getAngle() const
{
    return (m_angle);
}

void                                Snake::setMove(char mv)
{
    m_mv = mv;
}

void                                Snake::changeDir(bool dir, float rate)
{
    if (dir)
        m_angle+=3 * rate / 4.0;
    else
        m_angle-=3 * rate / 4.0;
    std::cout << "go " << (!dir ? "left" : "right") << " " << rate / 4.0 << std::endl;
}

void                                Snake::view(Map &map, Map::CaseType find)
{
    SMART(GeneticalNode)            tmp;
    float                           res;
    unsigned int                    it;

    it = find == Map::WALL ? 0 : 3;
    res = map.view(m_angle - 38, m_pos, find);
    tmp = boost::static_pointer_cast<GeneticalNode>(m_input->get_ass(Chanel::hash("_data"))->get_son_ref(it++)->get_ref());
    tmp->get_ass(Chanel::hash("Impulse"))->get_value()._f = res;
    res = map.view(m_angle, m_pos, find);
    tmp = boost::static_pointer_cast<GeneticalNode>(m_input->get_ass(Chanel::hash("_data"))->get_son_ref(it++)->get_ref());
    tmp->get_ass(Chanel::hash("Impulse"))->get_value()._f = res;
    res = map.view(m_angle + 38, m_pos, find);
    tmp = boost::static_pointer_cast<GeneticalNode>(m_input->get_ass(Chanel::hash("_data"))->get_son_ref(it++)->get_ref());
    tmp->get_ass(Chanel::hash("Impulse"))->get_value()._f = res;
}

void                                Snake::exec(Map &map, bool real)
{
    SMART(GeneticalNode)            tmp;

    for (unsigned int it = 0; it < 50; it++)
    {
        m_brain.exec();
        view(map, Map::WALL);
        view(map, Map::FOOD);
    }

    tmp = boost::static_pointer_cast<GeneticalNode>(m_output->get_ass(Chanel::hash("_data"))->get_son_ref(0)->get_ref());
    if (tmp->get_ass(Chanel::hash("Accu"))->get_value()._f > 3)
    {
        if (real)
            changeDir(true, tmp->get_ass(Chanel::hash("Accu"))->get_value()._f);
        if (m_mv && m_mv == 1)
            boost::static_pointer_cast<GeneticalNode>(m_good->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
        else if (m_mv && m_mv == 2)
             boost::static_pointer_cast<GeneticalNode>(m_bad->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
    }
    else
    {
        if (m_mv && m_mv == 2)
            boost::static_pointer_cast<GeneticalNode>(m_good->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
        else if (m_mv && m_mv == 1)
             boost::static_pointer_cast<GeneticalNode>(m_bad->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
    }
    tmp = boost::static_pointer_cast<GeneticalNode>(m_output->get_ass(Chanel::hash("_data"))->get_son_ref(1)->get_ref());
    if (tmp->get_ass(Chanel::hash("Accu"))->get_value()._f > 3)
    {
        if (real)
            changeDir(false, tmp->get_ass(Chanel::hash("Accu"))->get_value()._f);
        if (m_mv && m_mv == 2)
            boost::static_pointer_cast<GeneticalNode>(m_good->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
        else if (m_mv && m_mv == 1)
             boost::static_pointer_cast<GeneticalNode>(m_bad->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
    }
    else
    {
        if (m_mv && m_mv == 1)
            boost::static_pointer_cast<GeneticalNode>(m_good->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
        else if (m_mv && m_mv == 2)
             boost::static_pointer_cast<GeneticalNode>(m_bad->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
    }
    if (m_mv)
    {
        for (unsigned int it = 0; it < 50; it++)
        {
            m_brain.exec();
            view(map, Map::WALL);
            view(map, Map::FOOD);
        }
    }

    m_dir.first = std::cos(m_angle * 3.14 / 180);
    m_dir.second = std::sin(m_angle * 3.14 / 180);
    m_pos.first += m_dir.first * 0.5;
    m_pos.second += m_dir.second * 0.5;
    if (map.getCase(std::make_pair((int)m_pos.first, (int)m_pos.second))._type == Map::WALL)
    {
        for (unsigned int it = 0; it < 50; it++)
        {
            m_brain.exec();
            view(map, Map::WALL);
            view(map, Map::FOOD);
        }
        boost::static_pointer_cast<GeneticalNode>(m_bad->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
        m_pos.first = 25;
        m_pos.second = 25;
        m_angle = 0;
        m_lastEat = 0;
        return ;
    }
    m_lastEat++;
    if (map.getCase(std::make_pair((int)(m_pos.first + 0.5), (int)(m_pos.second + 0.5)))._type == Map::FOOD)
    {
        std::cout << "Good !" << std::endl;
        boost::static_pointer_cast<GeneticalNode>(m_good->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
        for (unsigned int it = 0; it < 50; it++)
        {
            m_brain.exec();
            view(map, Map::WALL);
            view(map, Map::FOOD);
        }
        m_lastEat = 0;
        map.getCase(std::make_pair((int)(m_pos.first + 0.5), (int)(m_pos.second + 0.5)))._type = Map::EMPTY;
    }
    if (map.getCase(std::make_pair((int)(m_pos.first - 0.5), (int)(m_pos.second - 0.5)))._type == Map::FOOD)
    {
        std::cout << "Good !" << std::endl;
        boost::static_pointer_cast<GeneticalNode>(m_good->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
        for (unsigned int it = 0; it < 50; it++)
        {
            m_brain.exec();
            view(map, Map::WALL);
            view(map, Map::FOOD);
        }
        m_lastEat = 0;
         map.getCase(std::make_pair((int)(m_pos.first - 0.5), (int)(m_pos.second - 0.5)))._type = Map::EMPTY;
    }
    if (m_lastEat > 50)
    {
        std::cout << "Aie!" << std::endl;
        //boost::static_pointer_cast<GeneticalNode>(m_bad->get_ref())->get_ass(Chanel::hash("Impulse"))->get_value()._f = 15;
        m_lastEat = 0;
    }
}
