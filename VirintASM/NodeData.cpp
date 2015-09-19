
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
    m_opt.push_back(std::make_pair("FREE", FREE));
    m_opt.push_back(std::make_pair("KILL", KILL));
    m_opt.push_back(std::make_pair("JMP", JMP));
    m_opt.push_back(std::make_pair("DESTROY", DESTROY));
    m_opt.push_back(std::make_pair("VAR", VAR));

    m_opt.push_back(std::make_pair("ATR", ATR));
    m_opt.push_back(std::make_pair("RPLS", RPLS));
    m_opt.push_back(std::make_pair("DST", DST));
    m_opt.push_back(std::make_pair("PW", PW));
    m_opt.push_back(std::make_pair("WGTH", WGTH));
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

void        NodeMaker::add_data(std::string &name, std::string &data)
{
    NodeData    *dataN = new NodeData;

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

std::pair<unsigned char, unsigned int> NodeMaker::get_value(std::string &value)
{
    unsigned int        add;
    unsigned char       type;
    std::string         tmp;

    try
    {
        if (value[0] == '@' || value[0] == '&')
        {
            tmp = value.substr(1);
            add = get_var(tmp);
            type =  GLOBAL_CHAN;
        }
        else
        {
            tmp = value;
            for (int it = 0; it < (int)m_opt.size(); it++)
            {
                if (!strcasecmp(m_opt[it].first.c_str(), tmp.c_str()))
                    return (std::make_pair(INSTRU, m_opt[it].second));
            }
            type = VALUE;
            add = boost::lexical_cast<unsigned int>(value);
        }
    }
    catch (boost::bad_lexical_cast)
    {
        throw (std::string("Syntax Error with : ") + value);
    }
    return (std::make_pair(type, add));
}

std::string     NodeMaker::get_value(unsigned int value)
{
    std::ostringstream  str;

    if (value >= OPT_RANGE && value < CHANNEL_RANGE)
    {
        for (int it = 0; it < (int)m_opt.size(); it++)
        {
            if (m_opt[it].second == value)
                str << "$" << m_opt[it].first;
        }
        if (!str.str().size())
            str << value;
    }
    else if (value >= CHANNEL_RANGE)
    {
        str << "@" << value - CHANNEL_RANGE;
    }
    else
    {
        str << value;
    }
    return (str.str());
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
    std::vector<SMART(ObjClass)> &lst = node->get_son();

    file << get_value(node->get_value()) << " ";
    if (lst.size())
    {
        file << " {";
        for (int it = 0; it < (int)lst.size(); it++)
        {
            dasm(file, CAST(GeneticalNode*)(lst[it].get()));
        }
        file << "}" << std::endl;
        file << std::endl;
    }
}

void        NodeMaker::make_node(std::string &name, std::string &str)
{
    NodeData    *Node;
    std::size_t pos = 0;

    Node = get_node(name);
    check_pile(Node);
    str += "begin " + name + "\n";
    Node->node = read_node(Node->data, pos, str);
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
    GeneticalNode   *res;
    std::ofstream   file(out.c_str(), std::ios_base::binary);

    if (!file.is_open())
        throw (std::string("Can't open out file"));
    res = get_node(m_main)->node.get();
    res->get_propriety()->height = 8;
    res->get_propriety()->len = 8;
    res->get_propriety()->range.push_back(std::make_pair(VALUE_RANGE, OPT_RANGE));
    res->get_propriety()->range.push_back(std::make_pair(OPT_RANGE, CHANNEL_RANGE));
    res->get_propriety()->range.push_back(std::make_pair(VALUE_RANGE, m_size));
    res->save(file);
}
