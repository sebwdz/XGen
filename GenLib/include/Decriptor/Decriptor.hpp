#ifndef DRECRIPTOR_HPP
#define DRECRIPTOR_HPP

#include        "Object/Movable.hpp"

class           Decriptor : public Movable
{
public:

    Decriptor(Object *obj);
    ~Decriptor();

    void            set_block(SMART(GeneticalNode) block);
    SMART(GeneticalNode) get_block() const;
    LineDecript     *get_line();

    virtual void    exec();
    virtual void    catch_signals();
    void            turn(GeneticalNode *node);
    GeneticalNode     *get_next_node(GeneticalNode *obj);

    /* value */

    float           get_value(GeneticalNode *node);
    SMART(GeneticalNode) get_chan(GeneticalNode *node);

    int             nothing(GeneticalNode *node);
    int             set_function(GeneticalNode *node);
    int             comparator(GeneticalNode *node, GeneticalNode *content);
    int             comp_funcion(GeneticalNode *node);
    int             loop(GeneticalNode *node);
    int             creat_function(GeneticalNode *node);
    int             use_function(GeneticalNode *node);
    int             decript_function(GeneticalNode *node);
    int             jmp_function(GeneticalNode *node);
    int             echo(GeneticalNode *node);
    int             copy(GeneticalNode *node);
    int             call(GeneticalNode* node);

    /* chan */

    void            set_chan(GeneticalNode *node);
    void            set_attach(bool attach);
    void            reset(SMART(GeneticalNode) obj);
    void            set_propriety(GeneticalNode *node, ChanPropriety *prop);

    /* signals */

    void            catch_simple(unsigned int code, void *sig);
    void            catch_duplic(unsigned int code, void *sig);

private:

    SMART(GeneticalNode)    m_block;
    unsigned int            m_jmp;
    SMART(GeneticalNode)    m_fast;
    bool                    m_attach;
};

#endif // DRECRIPTOR_HPP
