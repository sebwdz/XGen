
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
    view = sf::View(sf::Vector2f(brain->get_pos().first, brain->get_pos().second), sf::Vector2f(400, 400));
    view.zoom(1);
    setView(view);
    show_module(brain);
    display();
}

void        BrainView::show_link(ModuleClass *module)
{
    std::vector<ModuleClass*> const &links = module->get_links();

    for (unsigned int it = 0; it < links.size(); it++)
    {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(module->get_pos().first, module->get_pos().second)),
            sf::Vertex(sf::Vector2f(links[it]->get_pos().first, links[it]->get_pos().second))
        };
        draw(line, 2, sf::Lines);
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
    res = module->get_line()->get_chan(res + CHANNEL_RANGE)->get_value()._f * 200.0;
    res = res > 254 ? 254 : res;
    sf::Color cl(1, 0, res);

    str = "ImNucleusSplit";
    res = Chanel::hash(str);
    res = module->get_line()->get_chan(res + CHANNEL_RANGE)->get_value()._f * 20.0;
    if (res > 0)
      cl = sf::Color(200, 200, 200);
    str = "SalPrimary";
    res = Chanel::hash(str);
    res = module->get_line()->get_chan(res + CHANNEL_RANGE)->get_value()._f * 200.0;
 /*   str = "DopamineAct";
    res2 = Chanel::hash(str);
    res2 = module->get_line()->get_chan(res2 + CHANNEL_RANGE)->get_value() * 10.0;*/
    res = res > 254 ? 254 : res;
    if (res > 0)
      cl.g = res;
    str = "ImActive";
    res = Chanel::hash(str);
    res = module->get_line()->get_chan(res + CHANNEL_RANGE)->get_value()._f * 50.0;
    res = res > 254 ? 254 : res;
    if (res > 0)
      cl.r = res;
    cl.a = 200;
    shape.setPointCount(module->get_skeleton()->get_size());
    for (pt = module->get_skeleton()->get_begin(); pt != module->get_skeleton()->get_end(); pt++)
    {
        shape.setPoint(index++, sf::Vector2f(pt->first, pt->second));
    }
    shape.setFillColor(cl);
    shape.setOutlineThickness(0.8);
    shape.setOutlineColor(sf::Color(100, 100, 200));
    draw(shape);
    for (it = module->get_begin(); it != module->get_end(); it++)
    {
        if ((*it)->get_type() & TYPE_MODULE)
            show_module(CAST(ModuleClass*)(*it));
        else
            show_object(*it);
    }
    show_link(module);
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

