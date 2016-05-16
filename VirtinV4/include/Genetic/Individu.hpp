#ifndef INDIVIDU_HPP
#define INDIVIDU_HPP

#include            "GeneticalNode.hpp"

class               Individu
{
public:
    Individu();
    ~Individu();

    void            setFile(std::string const& str);
    std::string const &getFile();
    void            load();
    void            unload();
    void            save();

    bool            getCalculate();

    void                            generateByPatern(GeneticalNode*);
    SMART(GeneticalNode)            generate(GeneticalNode *patern);
    SMART(GeneticalNode)            getNodeByPatern(GeneticalNode *p);
    void                            getNodeSons(GeneticalNode*, GeneticalNode *p);
    void                            mutate(GeneticalNode *patern, boost::shared_ptr<GeneticalNode> node);
    SMART(Individu)                 cross(Individu*, GeneticalNode *p);
    SMART(GeneticalNode)            cross(GeneticalNode *n1, GeneticalNode *n2, GeneticalNode *p);

    float           getScore();
    void            evaluate();

private:
    SMART(GeneticalNode)    m_node;
    std::string             m_file;
    float                   m_score;
    bool                    m_calculate;
};

#endif // INDIVIDU_HPP
