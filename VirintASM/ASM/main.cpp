
#include        <vector>
#include        <boost/lexical_cast.hpp>
#include        "NodeMaker.hpp"


int make(std::vector<std::string> &conf)
{
    NodeMaker       *data = 0;
    std::ifstream   file;
    std::ofstream   out;
    int             it;
    std::string     str;
    bool            asmn;
    GeneticalNode   *node;

    try
    {
        if (conf.size() < 3)
            throw (std::string("[confa][out][filename]..."));
        it = 2;
        data = new NodeMaker(conf[0], asmn);
        while (it < (int)conf.size() && asmn)
        {
            file.open(conf[it].c_str());
            if (!file.is_open())
                throw (std::string("Can't open file ") + conf[it]);
            data->read_data(file);
            std::cout << "reader -> " << conf[it].c_str() << " succesfull" << std::endl;
            it++;
            file.close();
        }
        data->make_node(conf[0], str);
        data->save(conf[1]);
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
    std::cout << str << std::endl;
    if (data)
        delete data;
    return (0);
}

int     main(int ac, char **av)
{
    int it;
    std::vector<std::string>    str;

    if (ac > 1)
    {
        it = 1;
        while (av[it])
            str.push_back(std::string(av[it++]));
        make(str);
    }
}
