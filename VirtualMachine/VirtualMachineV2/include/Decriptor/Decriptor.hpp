#ifndef DRECRIPTOR_HPP
#define DRECRIPTOR_HPP

#include        "Genetic/GeneticalNode.hpp"
#include        "Object/Movable.hpp"

class           Decriptor : public Movable
{
public:

    Decriptor(Object *obj);
    ~Decriptor();

    void            set_node(SMART(GeneticalNode) node);
    LineDecript     *get_line();

    virtual void    exec();
    virtual void    catch_signals();
    void            turn(GeneticalNode *node);

    /* value */

    unsigned int    get_value(GeneticalNode *node);
    Chanel*         get_chan(GeneticalNode *node);

    int             nothing(GeneticalNode *node);
    int             set_function(GeneticalNode *node);
    int             comparator(GeneticalNode *node, GeneticalNode *content);
    int             comp_funcion(GeneticalNode *node);
    int             creat_function(GeneticalNode *node);
    int             use_function(GeneticalNode *node);
    int             decript_function(GeneticalNode *node);
    int             jmp_function(GeneticalNode *node);
    int             set_var_function(GeneticalNode *node);

    /* chan */

    void            set_chan(GeneticalNode *node);
    ChanPropriety   *get_propriety_chan(GeneticalNode *node, Chanel *chan, unsigned int ref);
    void            set_propriety(GeneticalNode *node, ChanPropriety *prop);

    /* signals */

    void            catch_simple(unsigned int code, void *sig);
    void            catch_duplic(unsigned int code, void *sig);

private:

    SMART(GeneticalNode)    m_node;
    unsigned int            m_jmp;
    USE_LIST                m_fast;
};

#endif // DRECRIPTOR_HPP
