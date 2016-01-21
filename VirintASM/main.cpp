#include    <QCoreApplication>
#include    <QTextEdit>
#include    <fstream>
#include    <iostream>
#include    <sstream>
#include    <boost/lexical_cast.hpp>
#include    "include/NodeMaker.hpp"

std::string         int_to_str(unsigned int value)
{
    std::string     res;
    std::ostringstream  os;

    os << value;
    res = os.str();
    return (res);
}

int make(std::vector<std::string> &conf, QTextEdit *edit)
{
    NodeMaker       *data = 0;
    std::ifstream   file;
    std::ofstream   out;
    int             it;
    std::string     str;
    bool            asmn;
    GeneticalNode   *node;
    std::vector<SMART(GeneticalNode)> vct;

    try
    {
        if (conf.size() < 4)
            throw (std::string("[conf][out][filename]..."));
        it = 3;
        std::cout << conf[1] << std::endl;
        if (conf[1].substr(conf[1].size() - 3) == "ASM")
            asmn = true;
        else
            asmn = false;
        data = new NodeMaker(conf[0], asmn);
        while (it < (int)conf.size() && asmn)
        {
            file.open(conf[it].c_str());
            if (!file.is_open())
                throw (std::string("Can't open file ") + conf[it]);
            data->read_data(file);
            it++;
            file.close();
        }
        if (asmn)
        {
            data->make_node(conf[0], str, vct);
            data->save(conf[2]);
        }
        else
        {
            file.open(conf[it - 1].c_str());
            out.open((conf[it].c_str()));
            node = new GeneticalNode();
            node->load(file);
            data->dasm(out, node);
        }
    }
    catch (std::string &st)
    {
        str += st;
    }
    catch (boost::bad_lexical_cast &error)
    {
        str += "Syntax Error\n";
    }
    catch (std::out_of_range &error)
    {
        str += "Syntax Error\n";
    }
    edit->clear();
    edit->insertPlainText(str.c_str());
    if (data)
        delete data;
    return (0);
}
