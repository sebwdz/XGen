#ifndef GENETICALALGO_HPP_INCLUDED
#define GENETICALALGO_HPP_INCLUDED

#include    "VirtualMachine/VirtualMachine.hpp"

class       GeneticalAlgo : public GeneticObj
{
public:
    GeneticalAlgo(GeneticObj *parent = 0);
    virtual ~GeneticalAlgo();

    virtual void        set_size(int size);
    void                set_engine(SMART(VirtualMachine) engine);

    int                 get_size();
    double              get_best();
    double              get_average();

    void                generate(int size);
    void                generate(GeneticalIndividu *individu, int size = 0);
    void                indject(GeneticalNode *node);

    virtual void        exec(int cycle);
    void                move_population(std::vector<SMART(ObjClass)> &to);
    void                add_individu(SMART(GeneticalIndividu) ind);

    void                sort_list();
    void                kill_weak();
    void                selection();

    void                cross(std::vector<SMART(ObjClass) > &node,
                            GeneticalIndividu *indiv1, GeneticalIndividu *indiv2);

    GeneticalIndividu   *get_individu(double value);

    virtual void        save(std::ofstream &file);
    virtual void        load(std::ifstream &file);
protected:

    int                         m_size;
    SMART(VirtualMachine)       m_engine;
    double                      m_best;
    double                      m_average;
    bool                        m_continue;
};

#endif // GENETICALALGO_HPP_INCLUDED
