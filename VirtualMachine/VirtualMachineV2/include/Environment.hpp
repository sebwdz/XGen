#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include            <boost/unordered_map.hpp>
#include            "VirtualMachine/VirtualMachine.hpp"
#include            "Cell/Brain.hpp"
#include            "SFML/Graphics.hpp"

#define             VOID        0
#define             FOOD        1
#define             CELL        2

class               Environment :  public MachineTester
{
public:
    Environment();
    ~Environment();

    void            init();
    void            set_brain(Brain *brain);
    Brain           *get_brain();
    void            exec();
    void            show(sf::RenderWindow *win);
    void            add_module(GeneticalNode *node, std::pair<float, float> &pos, bool sensor);
    float           get_food();
    float            get_sensor(std::pair<float, float> pos, std::pair<float, float> vct);

private:

    boost::unordered_map<std::pair<int, int>, int>  m_map;
    std::pair<float, float>                         m_pos;
    Brain                                           *m_brain;
    std::vector<SMART(ModuleClass)>                 m_sensor;
    std::vector<SMART(ModuleClass)>                 m_act;
    float                                           m_food;
    int                                             m_dir;
    int                                             m_lmv;
};

#endif // ENVIRONMENT_HPP
