
#include        <boost/lexical_cast.hpp>
#include        "include/NodeMaker.hpp"
#include        "Decriptor/Opt.hpp"
#include        "Decriptor/chanel.hpp"

NodeMaker::NodeMaker(std::string &maind, bool asmn)
{
    m_main = maind;
    m_opt.push_back(std::make_pair("SUP", SUP));
    m_opt.push_back(std::make_pair("INF", INF));
    m_opt.push_back(std::make_pair("EGAL", EGAL));
    m_opt.push_back(std::make_pair("XOR", XOR));
    m_opt.push_back(std::make_pair("OR", OR));
    m_opt.push_back(std::make_pair("AND", AND));
    m_opt.push_back(std::make_pair("NO", NO));
    m_opt.push_back(std::make_pair("USE", USE));
    m_opt.push_back(std::make_pair("UNUSE", UNUSE));
    m_opt.push_back(std::make_pair("SHARED", SHARED));
    m_opt.push_back(std::make_pair("UNSHARED", UNSHARED));
    m_opt.push_back(std::make_pair("ADD", ADD));
    m_opt.push_back(std::make_pair("SUB", SUB));
    m_opt.push_back(std::make_pair("SET", SET));
    m_opt.push_back(std::make_pair("CREAT", CREAT));
    m_opt.push_back(std::make_pair("DETACH", DETACH));
    m_opt.push_back(std::make_pair("NEW_HEAD", NEW_HEAD));
    m_opt.push_back(std::make_pair("DUPLIC", DUPLIC));
    m_opt.push_back(std::make_pair("ATTACH", ATTACH));
    m_opt.push_back(std::make_pair("LINK", LINK));
    m_opt.push_back(std::make_pair("UNLINK", UNLINK));
    m_opt.push_back(std::make_pair("TAKE_OUT", TAKEOUT));
    m_opt.push_back(std::make_pair("FREE", FREE));
    m_opt.push_back(std::make_pair("KILL", KILL));
    m_opt.push_back(std::make_pair("DESTROY", DESTROY));
    m_opt.push_back(std::make_pair("VAR", VAR));

    m_opt.push_back(std::make_pair("ATR", ATR));
    m_opt.push_back(std::make_pair("RPLS", RPLS));
    m_opt.push_back(std::make_pair("DST", DST));
    m_opt.push_back(std::make_pair("PW", PW));
    m_opt.push_back(std::make_pair("OTH", OTH));
    m_opt.push_back(std::make_pair("TO", TO));
    m_opt.push_back(std::make_pair("MV", MV));
    m_opt.push_back(std::make_pair("CHNG", CHNG));
    m_opt.push_back(std::make_pair("TYPE", TYPE));
    m_opt.push_back(std::make_pair("ACT", ACT));
    m_asm = asmn;
    m_size = 0;
}

NodeMaker::~NodeMaker()
{
    for (int it = 0; it < (int)m_node.size(); it++)
        delete m_node[it];
}

void        NodeMaker::extract_arg(NodeData *dataN, std::string str)
{
    int     it2 = 0;

    for (int it = 0; it < (int)str.size(); it++)
    {
        while (it < (int)str.size() && str[it] != ' ')
            it++;
        if (str[it] == ' ')
            it--;
        dataN->arg[str.substr(it2 + 1, it - it2)] = dataN->arg.size() - 1;
        if (it < str.size() - 1)
            it++;
        while (str[it] == ' ')
            it2 = it++;
    }
}

void        NodeMaker::add_data(std::string &name, std::string &data)
{
    NodeData                *dataN = new NodeData;
    std::size_t             it[2];

    if ((it[0] = name.find_first_of('(')) != std::string::npos)
    {
        it[1] = name.find_first_of(')', it[0]);
        extract_arg(dataN, name.substr(it[0], it[1] - it[0]));
        name = name.substr(0, it[0]);
    }
    dataN->name = name;
    dataN->data = data;
    m_node.push_back(dataN);
}

NodeData        *NodeMaker::get_node(std::string &name)
{
    for (int it = 0; it < (int)m_node.size(); it++)
        if (m_node[it]->name == name)
            return (m_node[it]);
    throw (std::string ("Can't find node : ") + name);
    return (0);
}

SMART(GeneticalNode)    NodeMaker::get_value(NodeData *data, std::string &value, std::vector<SMART(GeneticalNode)> &av)
{
    std::string             tmp;
    SMART(GeneticalNode)    node;
    unsigned int            v;

    try
    {
        if (value[0] == 0)
        {
            node = SMART(GeneticalNode)(new GeneticalNode());
            node->set_type(VALUE);
            return (node);
        }
        else if (value[0] == '$')
        {
            if (data->arg.find(value) == data->arg.end())
                throw (std::string(value + " isn't a valid argument"));
            v = data->arg[value];
            if (v >= (int)av.size())
                throw (std::string(value + " was not found, to few argument"));
            return (av[v]);
        }
        else if (value[0] == '@' || value[0] == '&')
        {
            node = SMART(GeneticalNode)(new GeneticalNode());
            tmp = value.substr(1);
            node->set_value(get_var(tmp));
            node->set_type(GLOBAL_CHAN);
        }
        else if (value[0] == '#')
        {
            node = SMART(GeneticalNode)(new GeneticalNode());
            node->set_value(Chanel::hash(value.substr(1)));
            node->set_type(FAST_CHAN);
        }
        else
        {
            node = SMART(GeneticalNode)(new GeneticalNode());
            for (int it = 0; it < (int)m_opt.size(); it++)
            {
                if (!strcasecmp(m_opt[it].first.c_str(), value.c_str()))
                {
                    node->set_type(INSTRU);
                    node->set_value(m_opt[it].second);
                    return (node);
                }
            }
            node->set_type(VALUE);
            node->set_value(boost::lexical_cast<unsigned int>(value));
        }
    }
    catch (boost::bad_lexical_cast)
    {
        throw (std::string("Syntax Error with : ") + value + std::string("."));
    }
    return (node);
}

unsigned int    NodeMaker::get_var(std::string &str)
{
    unsigned int                res;

    for (VAR_LIST::iterator it = m_var.begin(); it != m_var.end(); it++)
    {
        if (it->first == str)
            return (it->second);
    }
    res = Chanel::hash(str);
    m_var.push_back(std::make_pair(str, res));
    return (m_var.back().second);
}

void        NodeMaker::dasm(std::ofstream &file, GeneticalNode* node)
{
    /*std::vector<ObjClass*> &lst = node->get_son();

    file << get_value(node->get_value()) << " ";
    if (lst.size())
    {
        file << " {";
        for (int it = 0; it < (int)lst.size(); it++)
        {
            dasm(file, CAST(GeneticalNode*)(lst[it]));
        }
        file << "}" << std::endl;
        file << std::endl;
    }*/
}

void        NodeMaker::make_node(std::string &name, std::string &str, std::vector<SMART(GeneticalNode)> &av)
{
    NodeData    *Node;
    std::size_t pos = 0;

    Node = get_node(name);
    check_pile(Node);
    str += "begin " + name + "\n";
    Node->node = read_node(Node, pos, str, av);
    str += "finish " + name + " succesfull\n";
    m_pile.pop_back();
}

void            NodeMaker::check_pile(NodeData *data)
{
    for (int it = 0; it < (int)m_pile.size(); it++)
    {
        if (m_pile[it] == data)
            throw(std::string("Recursivity detected"));
    }
    m_pile.push_back(data);
}

void            NodeMaker::save(std::string &out)
{
    SMART(GeneticalNode)    res;
    std::ofstream   file(out.c_str(), std::ios_base::binary);

    if (!file.is_open())
        throw (std::string("Can't open out file"));
    res = get_node(m_main)->node;
    res->save(file);
}
