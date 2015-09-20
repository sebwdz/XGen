
#include    "include/NodeMaker.hpp"

std::string             remove_comment(std::string buff) {
    std::string res;

    std::size_t found;
    std::size_t pos;

    res = "";
    pos = 0;
    while (pos != std::string::npos) {
        found = buff.find_first_of("[", pos);
        if (found != std::string::npos) {
            res += buff.substr(pos, found - pos);
            pos = found + 1;
            found = buff.find_first_of("]", pos);
        }
        else
            res += buff.substr(pos);
        if (found != std::string::npos)
            pos = found + 1;
        else
            pos = found;
    }
    return (res);
}

void        NodeMaker::read_data(std::ifstream &file)
{
    std::string line;
    std::string buff;
    std::string name;
    std::string data;
    std::size_t found;
    std::size_t pos;

    while (getline(file, line))
        buff += line + " ";
    buff = remove_comment(buff);
    pos = 0;
    pos = buff.find_first_not_of("\t ");
    while ((found = buff.find_first_of("<", pos)) != std::string::npos)
    {
        name = buff.substr(pos, found - pos);
        pos = found + 1;
        found = buff.find_first_of(">", pos);
        data = buff.substr(pos, found - pos);
        pos = found + 1;
        pos = buff.find_first_not_of("\t ", pos);
        add_data(name, data);
    }
}


SMART(GeneticalNode)       NodeMaker::read_node(std::string &data, std::size_t &pos, std::string &str)
{
    SMART(GeneticalNode)   node(new GeneticalNode());
    SMART(GeneticalNode)   son;
    std::size_t             found;
    std::string             tmp;
    std::pair<unsigned char, unsigned int>      value;

    pos = data.find_first_not_of("\t ", pos);
    found = data.find_first_of("\t ()", pos);
    if (data[pos] == ':')
    {
        tmp = data.substr(pos + 1, found - (pos + 1));
        make_node(tmp, str);
        pos = found;
        return (get_node(tmp)->node);
    }
    tmp = data.substr(pos, found - pos);
    value = get_value(tmp);
    node->set_value(value.second);
    node->set_type(value.first);
    pos = data.find_first_not_of("\t ", found);
    if (data[pos] == '(')
    {
        pos++;
        pos = data.find_first_not_of("\t ", pos);
        while (data[pos] != ')')
        {
            son = read_node(data, pos, str);
            son->set_parent(node.get());
            node->add_son(son);
            pos = data.find_first_not_of("\t ", pos);
            if (std::string::npos == pos)
                throw (std::string("Error Expected ')'"));
        }
        pos++;
    }
    return (node);
}
