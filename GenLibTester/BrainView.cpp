
#include        "include/BrainView.hpp"
#include        <QX11Info>
#include        <X11/Xlib.h>
#include        <iostream>

BrainView::BrainView() : sf::RenderWindow(sf::VideoMode(800, 800), "tester")
{
}

BrainView::~BrainView()
{

}

void        BrainView::show_tester(Brain *brain)
{
    sf::View                view;

    clear();
    view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(400, 400));
    view.zoom(1);
    setView(view);
    show_module(brain);
    display();
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
        if ((*it)->get_type() & TYPE_MODULE)
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

