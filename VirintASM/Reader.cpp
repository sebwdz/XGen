
#include    <boost/lexical_cast.hpp>
#include    <boost/algorithm/string/replace.hpp>
#include    "include/NodeMaker.hpp"
#include        "Decriptor/chanel.hpp"

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

void        NodeMaker::read_define(std::string &data)
{
  std::size_t     pos;
  std::size_t     end;
  std::string     word;
  std::string     value;

  pos = 0;
  while ((pos = data.find_first_of("?", pos)) != std::string::npos)
    {
      end = data.find_first_of(" \t", pos);
      word = data.substr(pos, end - pos);
      pos = data.find_first_not_of(" \t", end);
      end = data.find_first_of(";", pos);
      value = data.substr(pos, end - pos);
      m_define[word] = value;
      pos = end;
    }
}

void            NodeMaker::apply_define(NodeData *from)
{
  unsigned int  it;
  boost::unordered_map<std::string, std::string>::iterator str;

  if (!from)
      from = m_node;
  for (it = 0; it < from->node.size(); it++)
    {
      if (!from->node[it]->block)
      {
        for (str = m_define.begin(); str != m_define.end(); str++)
            boost::replace_all(from->node[it]->data, str->first, str->second);
      }
      apply_define(from->node[it]);
    }
}

std::string NodeMaker::convert_string(std::string buff)
{
    std::string res;
    std::string tmp;

    std::size_t found;
    std::size_t pos;
    std::size_t it;

    res = "";
    pos = 0;
    while (pos != std::string::npos) {
        found = buff.find_first_of("\"", pos);
        if (found != std::string::npos) {
            res += buff.substr(pos, found - pos);
            pos = found + 1;
            it = pos;
            while (1)
            {
                found = buff.find_first_of("\"", it);
                if (buff[found - 1] != '\\')
                    break;
                it = found + 1;
            }
            tmp = buff.substr(pos, found - pos);
            it = 0;
            while (it < tmp.size())
            {
                if (it && tmp[it - 1] == '\\')
                {
                    if (tmp[it] == '"')
                        res += boost::lexical_cast<std::string>((int)'"') + " ";
                    else if (tmp[it] == 'n')
                        res += "10 ";
                    else if (tmp[it] == 't')
                        res += "9 ";
                }
                else if (tmp[it] != '\\' || (it && tmp[it - 1] == '\\'))
                    res += boost::lexical_cast<std::string>((int)tmp[it]) + " ";
                it++;
            }
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
    buff = convert_string(buff);
    pos = 0;
    pos = buff.find_first_not_of("\t\n ");
    while ((found = buff.find_first_of("<", pos)) != std::string::npos)
    {
        name = buff.substr(pos, found - pos);
        pos = found + 1;
        found = buff.find_first_of(">", pos);
        data = buff.substr(pos, found - pos);
        pos = found + 1;
        pos = buff.find_first_not_of("\t\n ", pos);
        if (name.size())
          add_data(name, data);
        else
          read_define(data);
    }
}

void          NodeMaker::read_lib(std::string const &str)
{
    SMART(GeneticalNode)            node(new GeneticalNode());
    NodeData                        *data = new NodeData();
    NodeData                        *subData;

    node->load_file(str);
    for (unsigned int it = 0; it < node->get_son().size(); it++)
    {
        if (Chanel::hash("__name__") == node->get_son()[it]->get_key())
            data->key = node->get_son()[it]->get_value()._ui;
        else
        {
            subData = new NodeData();
            subData->key = node->get_son()[it]->get_key();
            subData->block = node->get_son()[it]->get_son_ref(0);
            data->node.push_back(subData);
        }
    }
    m_node->node.push_back(data);
}


SMART(GeneticalNode)               NodeMaker::read_node(NodeData *data, std::size_t &pos,
                                                     std::string &str, std::vector<SMART(GeneticalNode)> &av)
{
    SMART(GeneticalNode)              node;
    SMART(GeneticalNode)              son;
    std::size_t                       found;
    std::string                       tmp;
    std::vector<SMART(GeneticalNode)> newAv;
    unsigned int                      key;

    found = data->data.find_first_of("\t \n(){}", pos);
    if (data->data[pos] == ':')
    {
        tmp = data->data.substr(pos + 1, found - (pos + 1));
        pos = data->data.find_first_not_of("\t\n ", found);
        if (data->data[pos] == '(')
        {
            pos++;
            pos = data->data.find_first_not_of("\t\n ", pos);
            while (data->data[pos] != ')')
            {
                son = read_node(data, pos, str, av);
                newAv.push_back(son);
                pos = data->data.find_first_not_of("\t\n ", pos);
                if (std::string::npos == pos)
                    throw (std::string("Error Expected ')'"));
            }
            pos++;
        }
        make_node(tmp, str, newAv);
        return (get_node(tmp)->block);
    }
    else if (data->data[pos] == '{')
    {
        pos++;
        while (data->data[pos] != '}')
        {
            pos = data->data.find_first_not_of("\t \n", pos);
            found = data->data.find_first_of("\t \n", pos);
            key = Chanel::hash(data->data.substr(pos, found - pos));
            pos = found;
            pos = data->data.find_first_not_of("\t \n", pos);
            son = read_node(data, pos, str, av);
            son->set_key(key);
            pos = data->data.find_first_not_of("\t\n ", pos);
            if (data->data[pos] != '}')
                throw (std::string("Error Expected '}'"));
            pos++;
            return (son);
        }
        pos++;
        return (node);
    }
    tmp = data->data.substr(pos, found - pos);
    node = get_value(data, tmp, av);
    pos = data->data.find_first_not_of("\t \n", found);
    if (data->data[pos] == '(')
    {
        pos++;
        pos = data->data.find_first_not_of(" \t\n", pos);
        while (data->data[pos] != ')')
        {
            son = read_node(data, pos, str, av);
            node->add_son(son);
            pos = data->data.find_first_not_of("\t\n ", pos);
            if (std::string::npos == pos)
                throw (std::string("Error Expected ')'"));
        }
        pos++;
    }
    return (node);
}
