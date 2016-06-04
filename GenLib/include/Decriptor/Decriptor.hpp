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
    SMART(GeneticalNode)    get_fast() const;
    void                    set_return(SMART(GeneticalNode) node);

    virtual void    exec();
    virtual void    catch_signals();
    boost::shared_ptr<GeneticalNode> turn(GeneticalNode *node);
    GeneticalNode     *get_next_node(GeneticalNode *obj);

    /* value */

    float           get_value(GeneticalNode *node);
    SMART(GeneticalNode) get_chan(GeneticalNode *node);
    SMART(GeneticalNode) getSubChan(SMART(GeneticalNode), std::vector<SMART(GeneticalNode)> &vct, unsigned int i);

    SMART(GeneticalNode) nothing(GeneticalNode *node);
    SMART(GeneticalNode) set_function(GeneticalNode *node);
    int comparator(GeneticalNode *node, GeneticalNode *content);
    SMART(GeneticalNode) comp_funcion(GeneticalNode *node);
    SMART(GeneticalNode) loop(GeneticalNode *node);
    SMART(GeneticalNode) creat_function(GeneticalNode *node);
    SMART(GeneticalNode) use_function(GeneticalNode *node);
    SMART(GeneticalNode) decript_function(GeneticalNode *node);
    SMART(GeneticalNode) echo(GeneticalNode *node);
    SMART(GeneticalNode) copy(GeneticalNode *node);
    SMART(GeneticalNode) copy_value(GeneticalNode *node);
    SMART(GeneticalNode) call(GeneticalNode* node);
    SMART(GeneticalNode) ref_function(GeneticalNode *node);
    SMART(GeneticalNode) node_size(GeneticalNode *node);
    SMART(GeneticalNode) ret(GeneticalNode *node);
    SMART(GeneticalNode) pow(GeneticalNode *node);
    SMART(GeneticalNode) rand(GeneticalNode *node);
    SMART(GeneticalNode) erase(GeneticalNode *node);
    SMART(GeneticalNode) move_pos(GeneticalNode *node);
    SMART(GeneticalNode) round(GeneticalNode *node);
    SMART(GeneticalNode) sqrt(GeneticalNode *node);
    SMART(GeneticalNode) key_exist(GeneticalNode *node);
    SMART(GeneticalNode) attach(GeneticalNode *node);
    SMART(GeneticalNode) free(GeneticalNode* node);
    SMART(GeneticalNode) incr(GeneticalNode* node);
    SMART(GeneticalNode) val(GeneticalNode* node);
    SMART(GeneticalNode) copy_one(GeneticalNode *node);

    /* chan */

    void            set_chan(GeneticalNode *node);
    void            set_attach(bool attach);
    bool            get_attach();
    void            reset(SMART(GeneticalNode) obj);
    void            set_propriety(GeneticalNode *node, ChanPropriety *prop);
    SMART(GeneticalNode)    get_return();

    /* signals */

    void            catch_simple(unsigned int code, void *sig);
    void            catch_duplic(unsigned int code, void *sig);

private:

    SMART(GeneticalNode)    m_return;
    SMART(GeneticalNode)    m_block;
    SMART(GeneticalNode)    m_last;
    unsigned int            m_jmp;
    SMART(GeneticalNode)    m_fast;
    bool                    m_lastComp;
    bool                    m_attach;
};

#endif // DRECRIPTOR_HPP
