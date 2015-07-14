
#include        "Environment.hpp"
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
    m_env = new RenderWindow(sf::VideoMode(800, 600), "word");
}

BrainView::~BrainView()
{

}

void        BrainView::show_tester(MachineTester *tester)
{
    Brain                   *brain;
    sf::View                view;
    sf::Clock               time;

    brain = CAST(Environment*)(tester)->get_brain();
    //Clear();
    clear();
    view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(250, 250));
    //view.Zoom(1.5);
    view.zoom(1.5);
    //view.SetCenter(brain->get_pos().first, brain->get_pos().second);
    view.setCenter(brain->get_pos().first, brain->get_pos().second);
    //SetView(view);
    setView(view);
    show_module(brain);
    //m_env->Clear();
    m_env->clear();
    CAST(Environment*)(tester)->show(m_env);
    //m_env->Display();
    m_env->display();
    repaint();
    //Display();
    display();
}

void        BrainView::show_module(ModuleClass *module)
{
    //sf::Shape               shape;
    sf::ConvexShape           shape;
    OBJECT_LIST::iterator   it;
    POINT_LIST::iterator    pt;
    std::string             str("IMPULSE");
    unsigned int            res;
    int                     index = 0;

    res = Chanel::hash(str);
    res = module->get_line()->get_chan(res + CHANNEL_RANGE)->get_value() * 10;
    res = res > 254 ? 254 : res;
    sf::Color cl(res, 0, 0);
    str = "EXIT";
    res = Chanel::hash(str);
    res = module->get_line()->get_chan(res + CHANNEL_RANGE)->get_value() * 10;
    res = res > 254 ? 254 : res;
    cl.g = res;
    cl.a = 150;
    shape.setPointCount(module->get_skeleton()->get_size());
    for (pt = module->get_skeleton()->get_begin(); pt != module->get_skeleton()->get_end(); pt++)
    {
        shape.setPoint(index++, sf::Vector2f(pt->first, pt->second));
        //shape.AddPoint(pt->first, pt->second, cl, sf::Color(50, 50, 100));
    }
    //shape.SetOutlineWidth(0.5);
    shape.setFillColor(cl);
    shape.setOutlineThickness(0.8);
    shape.setOutlineColor(sf::Color(50, 50, 100));
    //Draw(shape);
    draw(shape);
    for (it = module->get_begin(); it != module->get_end(); it++)
    {
        if (CAST(ModuleClass*)(it->get()))
            show_module(CAST(ModuleClass*)(it->get()));
        else
            show_object(it->get());
    }
}

void        BrainView::show_object(Object *obj)
{
    //sf::Shape               shape;
    sf::RectangleShape          shape;
    std::pair<float, float>     pos;

    pos = obj->get_pos();
    sf::Color cl(0, 200, 100);
    //shape = sf::Shape::Line(-0.5, -0, 1, 0.5, 1, cl, 1, sf::Color(19, 20, 120));
    shape = sf::RectangleShape(sf::Vector2f(-0.5, 0.5));
    //shape.Move(pos.first, pos.second);
    shape.move(pos.first, pos.second);
    shape.setFillColor(cl);
    shape.setOutlineThickness(0.8);
    shape.setOutlineColor(sf::Color(50, 50, 100));
    //shape.Rotate(rand() % 360);
    shape.rotate(rand() % 360);
    //Draw(shape);
    draw(shape);
}

QPaintEngine*   BrainView::paintEngine() const
{
    return (0);
}

void        BrainView::paintEvent(QPaintEvent *envent)
{
    //Display();
    display();
}

void        BrainView::showEvent(QShowEvent*event)
{

    if (!m_init)
       {
           XFlush(QX11Info::display());
           //Create(winId());
           RenderWindow::create(winId());
           m_init = true;
       }
}
