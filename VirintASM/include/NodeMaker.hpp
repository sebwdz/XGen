#ifndef NODEMAKER_HPP
#define NODEMAKER_HPP

#include        "Genetic/GeneticalNode.hpp"

typedef struct  NodeData
{
    std::string                         name;
    std::string                         data;
    boost::unordered_map<std::string, unsigned int>   arg;
    SMART(GeneticalNode)                block;
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
    std::string     convert_string(std::string buff);
    void            make_node(std::string &name, std::string &str, std::vector<SMART(GeneticalNode)> &av);
    SMART(GeneticalNode)    get_value(NodeData *data, std::string &value, std::vector<SMART(GeneticalNode)> &av);
    SMART(GeneticalNode) read_node(NodeData *data, std::size_t &pos, std::string &str, std::vector<SMART(GeneticalNode)> &av);
    void            check_pile(NodeData *data);
    unsigned int    get_var(std::string &str);
    void        extract_arg(NodeData *dataN, std::string str);
    void        read_define(std::string &data);
    void        apply_define();

private:

    std::vector<NodeData*>   m_node;
    std::string              m_main;
    std::vector<std::pair<std::string, unsigned int> >   m_opt;
    VAR_LIST                                             m_var;
    std::vector<NodeData*>   m_pile;
    bool                    m_asm;
    unsigned int            m_size;
    boost::unordered_map<std::string, std::string>      m_define;
};

#endif // NODEMAKER_HPP
