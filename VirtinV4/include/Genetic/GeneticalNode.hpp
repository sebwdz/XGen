#ifndef GENETICALNODE_HPP_INCLUDED
#define GENETICALNODE_HPP_INCLUDED

#include    "Genetic/GeneticObj.hpp"

typedef class Decriptor Decriptor;

class   GeneticalNode : public GeneticObj
{
    public :
        GeneticalNode(GeneticObj *parent = 0);
        virtual ~GeneticalNode();

        void        load(std::ifstream &stream);
        void        save(std::ofstream &stream);

        void            set_value(unsigned int value);
        void            set_type(unsigned char type);
        void            set_len(int len);
        void            set_function(int (Decriptor::*fonction)(GeneticalNode *));
        unsigned int    get_value();
        unsigned char   get_type();
        int             (Decriptor::*get_function())(GeneticalNode *);

        void        cross_node(GeneticalNode *node1, GeneticalNode *node2, int croos);
        void        cross_child(GeneticalNode *node1, GeneticalNode *node2, int cross);

        void        mutate(double ratio);
        int         move_node(SMART(ObjClass) cp, GeneticalNode *from, int _move);

        void        generate();

        virtual SMART(ObjClass)    copy(SMART(ObjClass) cp = SMART(ObjClass)());

        GeneticalNode *get_obj(int &move, GeneticalNode *from, int parent);

    protected:

        unsigned int                            m_value;
        unsigned char                           m_type;
        int                                     (Decriptor::*m_function)(GeneticalNode*);
};

#endif // GENETICALNODE_HPP_INCLUDED
