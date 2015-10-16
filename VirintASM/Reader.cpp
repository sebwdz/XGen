
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


SMART(GeneticalNode)               NodeMaker::read_node(NodeData *data, std::size_t &pos, std::string &str, std::vector<SMART(GeneticalNode)> &av)
{
    SMART(GeneticalNode)                                    node;
    SMART(GeneticalNode)                                    son;
    std::size_t                                             found;
    std::string                                             tmp;
    std::vector<SMART(GeneticalNode)>                       newAv;

    pos = data->data.find_first_not_of("\t ", pos);
    found = data->data.find_first_of("\t ()", pos);
    if (data->data[pos] == ':')
    {
        tmp = data->data.substr(pos + 1, found - (pos + 1));
        pos = data->data.find_first_not_of("\t ", found + 1);
        if (data->data[pos] == '(')
        {
            pos++;
            pos = data->data.find_first_not_of("\t ", pos);
            while (data->data[pos] != ')')
            {
                son = read_node(data, pos, str, av);
                newAv.push_back(son);
                pos = data->data.find_first_not_of("\t ", pos);
                if (std::string::npos == pos)
                    throw (std::string("Error Expected ')'"));
            }
            pos++;

        }
        make_node(tmp, str, newAv);
        return (get_node(tmp)->node);
    }
    tmp = data->data.substr(pos, found - pos);
    node = get_value(data, tmp, av);
    pos = data->data.find_first_not_of("\t ", found);
    if (data->data[pos] == '(')
    {
        pos++;
        pos = data->data.find_first_not_of("\t ", pos);
        while (data->data[pos] != ')')
        {
            son = read_node(data, pos, str, av);
            node->add_son(son);
            pos = data->data.find_first_not_of("\t ", pos);
            if (std::string::npos == pos)
                throw (std::string("Error Expected ')'"));
        }
        pos++;
    }
    return (node);
}
