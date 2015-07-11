#ifndef NODEMAKER_HPP
#define NODEMAKER_HPP

#include        "Genetic/GeneticalNode.hpp"

typedef struct  NodeData
{
    std::string     name;
    std::string     data;
    SMART(GeneticalNode)   node;
} NodeData;

class   NodeMaker
{
public:

    NodeMaker(std::string &maind, bool asmn = true);
    ~NodeMaker();

    void            save(std::string &out);

    void            add_data(std::string &name, std::string &data);
    NodeData        *get_node(std::string &name);
    void            read_data(std::ifstream &file);
    void            dasm(std::ofstream &file, GeneticalNode *node);
    void            make_node(std::string &name, std::string &str);
    unsigned int    get_value(std::string &value);
    std::string     get_value(unsigned int value);
    boost::shared_ptr<GeneticalNode> read_node(std::string &data, std::size_t &pos, std::string &str);
    void            check_pile(NodeData *data);
    unsigned int    get_var(std::string &str);

private:

    std::vector<NodeData*>   m_node;
    std::string              m_main;
    std::vector<std::pair<std::string, unsigned int> >   m_opt;
    VAR_LIST                                             m_var;
    std::vector<NodeData*>   m_pile;
    bool                    m_asm;
    unsigned int            m_size;
};

#endif // NODEMAKER_HPP
