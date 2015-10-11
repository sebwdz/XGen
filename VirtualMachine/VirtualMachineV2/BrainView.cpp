
#include        "Tester.hpp"
#include        "Cell/Brain.hpp"
#include        "BrainView.hpp"
#include        <QX11Info>
#include        <X11/Xlib.h>
#include        <SFML/Graphics.hpp>

BrainView::BrainView() : MachineViewWidget(), sf::RenderWindow()
{
    setAttribute(Qt::WA_PaintOnScreen);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAttribute(Qt::WA_NoSystemBackground);
    setFocusPolicy(Qt::StrongFocus);

    resize(800, 800);
    m_init = false;
}

BrainView::~BrainView()
{

}

void        BrainView::show_tester(MachineTester *tester)
{
    Brain                   *brain;
    sf::View                view;

    brain = CAST(Tester*)(tester)->get_brain();
    clear();
    view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(250, 250));
    view.zoom(3);
    setView(view);
    show_map(brain->get_map());
    show_module(brain);
    repaint();
    display();
}

void        BrainView::show_map(ClassMap *map)
{
    boost::bimap<std::pair<int, int>, SMART(LnkCase)>::left_map::iterator  it;
    OBJECT_LIST::iterator                                                  obj;
    int                                                                    size;

    size = map->get_size() / 5;
    for (it = map->get_begin(); it != map->get_end(); it++)
    {
        if (it->second->get_case())
        {
            sf::RectangleShape  rect;
            if (!map->get_lnk() || !map->get_lnk()->get_map())
                rect.setFillColor(sf::Color(0, 200, 100, 130));
            else if (!map->get_lnk()->get_map()->get_lnk() || !map->get_lnk()->get_map()->get_lnk()->get_map())
                rect.setFillColor(sf::Color(255, 0, 0, 130));
            else
                rect.setFillColor(sf::Color(0, 0, 255, 130));
            rect.setSize(sf::Vector2f(size, size));
            rect.setPosition(it->second->get_pos().first * size - size / 2,
                             it->second->get_pos().second * size - size / 2);
            rect.setOutlineColor(sf::Color::Black);
            rect.setOutlineThickness(0.5);
            draw(rect);
        }
        if (CAST(ClassMap*)(it->second->get_case()))
            show_map(CAST(ClassMap*)(it->second->get_case()));
    }
}

void        BrainView::show_module(ModuleClass *module)
{
    sf::ConvexShape           shape;
    OBJECT_LIST::iterator   it;
    POINT_LIST::iterator    pt;
    std::string             str("Impulse");
    unsigned int            res;
    int                     index = 0;

    res = Chanel::hash(str);
    res = module->get_line()->get_chan(res + CHANNEL_RANGE)->get_value() * 20;
    res = res > 254 ? 254 : res;
    sf::Color cl(res, 0, 0);
    str = "impulseStk";
    res = Chanel::hash(str);
    res = module->get_line()->get_chan(res + CHANNEL_RANGE)->get_value() * 20;
    res = res > 254 ? 254 : res;
    cl.g = res;
    cl.a = 100;
    shape.setPointCount(module->get_skeleton()->get_size());
    for (pt = module->get_skeleton()->get_begin(); pt != module->get_skeleton()->get_end(); pt++)
    {
        shape.setPoint(index++, sf::Vector2f(pt->first, pt->second));
    }
    shape.setFillColor(cl);
    shape.setOutlineThickness(0.8);
    shape.setOutlineColor(sf::Color(50, 50, 100));
    draw(shape);
    for (it = module->get_begin(); it != module->get_end(); it++)
    {
        if (CAST(ModuleClass*)(*it))
            show_module(CAST(ModuleClass*)(*it));
        else
            show_object(*it);
    }
}

void        BrainView::show_object(Object *obj)
{
    sf::RectangleShape          shape;
    std::pair<float, float>     pos;

    pos = obj->get_pos();
    sf::Color cl(0, 200, 100);
    shape = sf::RectangleShape(sf::Vector2f(-0.5, 0.5));
    shape.move(pos.first, pos.second);
    shape.setFillColor(cl);
    shape.setOutlineThickness(0.8);
    shape.setOutlineColor(sf::Color(50, 50, 100));
    shape.rotate(rand() % 360);
    draw(shape);
}

QPaintEngine*   BrainView::paintEngine() const
{
    return (0);
}

void        BrainView::paintEvent(QPaintEvent *event)
{
    (void)event;
    display();
}

void        BrainView::showEvent(QShowEvent*event)
{
    if (!m_init)
       {
           XFlush(QX11Info::display());
           RenderWindow::create(winId());
           m_init = true;
       }
}
