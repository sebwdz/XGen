
#include    "Decriptor/Decriptor.hpp"

SMART(GeneticalNode)        str_to_node(char *str)
{
    SMART(GeneticalNode)    r(new GeneticalNode());
    unsigned int            it = 0;

    r->get_value()._f = 2;
    while (str[it])
    {
        r->get_son_ref(it)->get_value()._f = str[it];
        it++;
    }
    return (r);
}

SMART(GeneticalNode)        get_av(char **av)
{
    SMART(GeneticalNode)    r(new GeneticalNode());

    while (*av)
    {
        r->add_son(str_to_node(*av));
        av++;
    }
    return (r);
}

int         main(int ac, char **av)
{
    SMART(GeneticalNode)    node(new GeneticalNode());
    Decriptor               *decript = new Decriptor(NULL);

    srandom(time(NULL));
    if (ac < 2)
        return (0);
    try {
        node->load_file(av[1]);
        get_av(av + 2)->copy(decript->get_fast()->get_ass(Chanel::hash("str_av")));
        decript->set_block(node);
        decript->exec();
        if (decript->get_return())
            return ((int)decript->get_return()->get_value()._f);
    } catch (std::exception)
    {
        return (84);
    }
    catch (std::string)
    {
        return (84);
    }

    return (0);
}
