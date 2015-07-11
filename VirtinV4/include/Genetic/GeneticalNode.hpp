#ifndef GENETICALNODE_HPP_INCLUDED
#define GENETICALNODE_HPP_INCLUDED

#include    "Genetic/GeneticObj.hpp"

class   GeneticalNode : public GeneticObj
{
    public :
        GeneticalNode(GeneticObj *parent = 0);
        virtual ~GeneticalNode();

        void        load(std::ifstream &stream);
        void        save(std::ofstream &stream);

        void            set_value(unsigned int value);
        void            set_len(int len);
        unsigned int    get_value();

        void        cross_node(GeneticalNode *node1, GeneticalNode *node2, int croos);
        void        cross_child(GeneticalNode *node1, GeneticalNode *node2, int cross);

        void        mutate(double ratio);
        int         move_node(SMART(ObjClass) cp, GeneticalNode *from, int _move);

        void        generate();

        virtual SMART(ObjClass)    copy(SMART(ObjClass) cp = SMART(ObjClass)());

        GeneticalNode *get_obj(int &move, GeneticalNode *from, int parent);

    protected:

        unsigned int                            m_value;
};

#endif // GENETICALNODE_HPP_INCLUDED
