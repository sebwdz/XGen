#ifndef GENETICALNODE_HPP_INCLUDED
#define GENETICALNODE_HPP_INCLUDED

#include    "Genetic/GeneticObj.hpp"

typedef class Decriptor     Decriptor;
typedef class Chanel        Chanel;
typedef class GeneticBlock  GeneticBlock;

typedef union u_nodeValue {
  float         _f;
  unsigned char _uc;
  unsigned int  _ui;
} nodeValue;

class   GeneticalNode : public GeneticObj
{
    public :
        GeneticalNode(GeneticObj *parent = 0);
        virtual ~GeneticalNode();

        void        load(std::ifstream &stream);
        void        save(std::ofstream &stream);

        void            set_block(GeneticBlock *block);
        void            set_value(nodeValue &value);
        void            set_chan(Chanel *chan);
        void            set_function(int (Decriptor::*fonction)(GeneticalNode*));
        nodeValue       &get_value();
        int             (Decriptor::*get_function())(GeneticalNode *);
        Chanel          *get_chan();
        GeneticBlock    *get_block();

        virtual SMART(ObjClass)    copy(SMART(ObjClass) cp = SMART(ObjClass)());

        GeneticalNode *get_obj(int &move, GeneticalNode *from, int parent);

    protected:

        nodeValue                               m_value;
        int                                     (Decriptor::*m_function)(GeneticalNode*);
        Chanel                                  *m_chan;
        GeneticBlock                            *m_block;
};

#endif // GENETICALNODE_HPP_INCLUDED
