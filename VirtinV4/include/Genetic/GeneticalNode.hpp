#ifndef GENETICALNODE_HPP_INCLUDED
#define GENETICALNODE_HPP_INCLUDED

#include    <boost/unordered_map.hpp>
#include    "Genetic/GeneticObj.hpp"
#include    "Serialize.hpp"

typedef class Decriptor     Decriptor;
typedef class Chanel        Chanel;
typedef class GeneticBlock  GeneticBlock;

#define     USE_LIST        boost::unordered_map<unsigned int, SMART(GeneticalNode)>

class   GeneticalNode : public GeneticObj
{
    public :
        GeneticalNode(GeneticObj *parent = 0);
        virtual ~GeneticalNode();

        void                    load(std::ifstream &stream);
        void                    save(std::ofstream &stream);

        void                    set_block(GeneticalNode *block);
        void                    set_chan(boost::shared_ptr<GeneticalNode> chan);
        void                    set_function(SMART(GeneticalNode) (Decriptor::*fonction)(GeneticalNode*));

        SMART(GeneticalNode)    (Decriptor::*get_function())(GeneticalNode*);
        SMART(GeneticalNode)    &get_chan();
        GeneticalNode           *get_block();

        SMART(GeneticalNode)    get_ass(unsigned int key, bool creat = true);
        SMART(GeneticalNode)    &get_son_ref(unsigned int ref);

        void                    remove_ass(unsigned int key);
        void                    set_ass(unsigned int key, SMART(GeneticalNode) node);
        void                    add_son(boost::shared_ptr<GeneticalNode> son);
        SMART(GeneticalNode)    get_local();
        Serialize               *serialize();
        char                    *deserialize(char*);

        void                    set_type(int type);

        USE_LIST                &get_ass();
        std::vector<SMART(GeneticalNode)> &get_son();

        virtual SMART(GeneticalNode)    copy(SMART(GeneticalNode) cp = SMART(GeneticalNode)());

        GeneticalNode *get_obj(int &move, GeneticalNode *from, int parent);

    protected:

        SMART(GeneticalNode)                (Decriptor::*m_function)(GeneticalNode*);
        SMART(GeneticalNode)                m_chan;
        GeneticalNode                       *m_block;
        USE_LIST                            m_ass;
        SMART(GeneticalNode)                m_local;
        std::vector<SMART(GeneticalNode)>   m_son;
};

#endif // GENETICALNODE_HPP_INCLUDED
