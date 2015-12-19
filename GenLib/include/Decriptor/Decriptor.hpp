#ifndef DRECRIPTOR_HPP
#define DRECRIPTOR_HPP

#include        "Object/Movable.hpp"

class           Decriptor : public Movable
{
public:

    Decriptor(Object *obj);
    ~Decriptor();

    void            set_block(boost::shared_ptr<GeneticObj> block);
    SMART(GeneticObj) get_block() const;
    LineDecript     *get_line();

    virtual void    exec();
    virtual void    catch_signals();
    void            turn(GeneticalNode *node);
    GeneticalNode     *get_next_node(GeneticObj *obj);

    /* value */

    float           get_value(GeneticalNode *node);
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
    int             echo(GeneticalNode *node);

    /* chan */

    void            set_chan(GeneticalNode *node);
    void            set_attach(bool attach);
    void            reset(boost::shared_ptr<GeneticObj> obj);
    void            set_propriety(GeneticalNode *node, ChanPropriety *prop);

    /* signals */

    void            catch_simple(unsigned int code, void *sig);
    void            catch_duplic(unsigned int code, void *sig);

private:

    SMART(GeneticObj)       m_block;
    unsigned int            m_jmp;
    USE_LIST                m_fast;
    bool                    m_attach;
};

#endif // DRECRIPTOR_HPP
