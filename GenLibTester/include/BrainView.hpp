#ifndef BRAINVIEW_HPP
#define BRAINVIEW_HPP

#include        <SFML/Graphics.hpp>
#include        "Cell/Brain.hpp"

class           BrainView : public sf::RenderWindow
{
public:
    BrainView();
    virtual ~BrainView();

    void            show_tester(Brain *brain);
    void            show_module(ModuleClass *module);
    void            show_object(Object *obj);

private:

    bool        m_init;
};

#endif // BRAINVIEW_HPP
