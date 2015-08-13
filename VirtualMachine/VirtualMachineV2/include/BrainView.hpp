#ifndef BRAINVIEW_HPP
#define BRAINVIEW_HPP

#include        <SFML/Graphics.hpp>
#include        "Cell/Module.hpp"
#include        "Plugin.hpp"

class           BrainView : public MachineViewWidget, public sf::RenderWindow
{
public:
    BrainView();
    virtual ~BrainView();

    void            show_tester(MachineTester *tester);
    void            show_module(ModuleClass *module);
    void            show_map(ModuleClass *map);
    void            show_object(Object *obj);
    void            paintEvent(QPaintEvent *event);
    void            showEvent(QShowEvent*event);
    QPaintEngine*   paintEngine() const;

private:

    RenderWindow    *m_env;
    bool        m_init;
};

#endif // BRAINVIEW_HPP
