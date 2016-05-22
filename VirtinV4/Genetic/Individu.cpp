
#include                "Decriptor/chanel.hpp"
#include                "Decriptor/Opt.hpp"
#include                "Individu.hpp"

Individu::Individu()
{
    m_calculate = false;
}

Individu::~Individu()
{

}

void            Individu::setFile(std::string const& str)
{
    m_file = str;
}

std::string const &Individu::getFile()
{
    return (m_file);
}

void            Individu::load()
{
    m_node = SMART(GeneticalNode)(new GeneticalNode);
    m_node->load_file(m_file);
}

void            Individu::unload()
{
    m_node = SMART(GeneticalNode)();
}

void            Individu::save()
{
    m_node->save_file(m_file);
}

void                            Individu::generateByPatern(GeneticalNode *patern)
{
    m_node = generate(patern);
}

SMART(GeneticalNode)            Individu::generate(GeneticalNode *patern)
{
    SMART(GeneticalNode)        node;
    SMART(GeneticalNode)        son;

    if (!(patern->get_type() == INSTRU && patern->get_value()._ui == GEN))
    {
        node = SMART(GeneticalNode)(new GeneticalNode());
        node->get_value() = patern->get_value();
        node->set_type(patern->get_type());
        node->set_key(patern->get_key());
        for (unsigned int it = 0; it < patern->get_son().size(); it++)
        {
            son = generate(patern->get_son_ref(it).get());
            node->add_son(son);
        }
    }
    else
    {
        node = getNodeByPatern(patern);
        getNodeSons(node.get(), patern);
    }
    return (node);
}

SMART(GeneticalNode)        Individu::getNodeByPatern(GeneticalNode *p)
{
    SMART(GeneticalNode)    node;
    SMART(GeneticalNode)    tmp;
    unsigned int            choice;
    std::pair<int, int>     range;

    if ((tmp = p->get_ass(Chanel::hash("_val"), false)))
    {
        if (tmp->get_value()._ui == Chanel::hash("_range"))
        {
            node = SMART(GeneticalNode)(new GeneticalNode);
            range.first = p->get_ass(Chanel::hash("_valmax"))->get_value()._f;
            range.second = p->get_ass(Chanel::hash("_valmin"))->get_value()._f;
            if (range.first > range.second)
                node->get_value()._f = (rand() % (range.first - range.second + 1)) + range.second;
        }
        else if (tmp->get_value()._ui == Chanel::hash("_choice"))
        {
            tmp = p->get_ass(Chanel::hash("_choice"));
            if (tmp->get_son().size())
            {
                choice = rand() % tmp->get_son().size();
                node = generate(tmp->get_son_ref(choice).get());
            }
        }
    }
    if (!node)
     node = SMART(GeneticalNode)(new GeneticalNode);
    return (node);
}

void            Individu::getNodeSons(GeneticalNode *node, GeneticalNode *p)
{
    SMART(GeneticalNode)    tmp;
    SMART(GeneticalNode)    son;
    unsigned int            nb;
    std::pair<int, int>     range;

    if ((tmp = p->get_ass(Chanel::hash("_son"), false)))
    {
        if ((son = p->get_ass(Chanel::hash("_soninf"), false)))
        {
            if (node->get_son().size() >= son->get_value()._f)
                return ;
        }
        if ((son = p->get_ass(Chanel::hash("_sonsup"), false)))
        {
            if (node->get_son().size() <= son->get_value()._f)
                return ;
        }
        range.first = p->get_ass(Chanel::hash("_sonmax"))->get_value()._f;
        range.second = p->get_ass(Chanel::hash("_sonmin"))->get_value()._f;
        if (range.first <= range.second)
            nb = range.first;
        else
            nb = (rand() % (range.first - range.second + 1)) + range.second;
        for (unsigned int it = 0; it < nb; it++)
        {
            son = generate(tmp.get());
            node->add_son(son);
        }
    }
}

void            Individu::mutate(GeneticalNode *p, SMART(GeneticalNode) node)
{
    SMART(GeneticalNode)        tmp;
    std::pair<int, int>         range;
    int                         choice;

    if (!node)
        node = m_node;
    if ((p->get_type() == INSTRU && p->get_value()._ui == GEN))
    {
        if ((tmp = p->get_ass(Chanel::hash("_val"), false)))
        {
            if (rand() % 1000 > 900)
            {
                if (tmp->get_value()._ui == Chanel::hash("_range"))
                {
                    range.first = p->get_ass(Chanel::hash("_valmax"))->get_value()._f;
                    range.second = p->get_ass(Chanel::hash("_valmin"))->get_value()._f;
                    if (range.first > range.second)
                        node->get_value()._f = (rand() % (range.first - range.second + 1)) + range.second;
                }
                else if (tmp->get_value()._ui == Chanel::hash("_choice"))
                {
                    tmp = p->get_ass(Chanel::hash("_choice"));
                    if (tmp->get_son().size())
                    {
                        choice = rand() % tmp->get_son().size();
                        tmp = generate(tmp->get_son_ref(choice).get());
                        if (tmp->get_son().size())
                            tmp->copy(node);
                        else
                        {
                            node->set_type(tmp->get_type());
                            node->get_value() = tmp->get_value();
                        }
                    }
                }
            }
        }
        if ((tmp = p->get_ass(Chanel::hash("_son"), false)))
        {
            if (rand() % 1000 > 900)
            {
                range.first = p->get_ass(Chanel::hash("_sonmax"))->get_value()._f;
                range.second = p->get_ass(Chanel::hash("_sonmin"))->get_value()._f;
                choice = rand() % 100;
                if (choice && (int)node->get_son().size() < range.first)
                {
                    choice = 0;
                    if (node->get_son().size())
                        choice = rand() % node->get_son().size();
                    node->add_son(generate(tmp.get()));
                }
                else if (choice <= 50 && node->get_son().size() && (int)node->get_son().size() - 1 >= range.second)
                {
                    choice = rand() % node->get_son().size();
                    if (node->get_son_ref(choice)->get_key())
                        node->remove_ass(node->get_son_ref(choice)->get_key());
                    node->get_son().erase(node->get_son().begin() + choice);
                }
            }
        }
    }
    for (unsigned int it = 0; it < node->get_son().size(); it++)
        mutate(p->get_son_ref(it).get(), node->get_son_ref(it));
}

SMART(Individu)                 Individu::cross(Individu *oth, GeneticalNode *p)
{
    SMART(Individu)             ind(new Individu);

    ind->m_node = cross(m_node.get(), oth->m_node.get(), p);
    return (ind);
}

SMART(GeneticalNode)            Individu::cross(GeneticalNode *n1, GeneticalNode *n2, GeneticalNode *p)
{
    SMART(GeneticalNode)        res(new GeneticalNode);
    SMART(GeneticalNode)        tmp;
    GeneticalNode               *x;

    if ((p->get_type() == INSTRU && p->get_value()._ui == GEN))
    {
        if (rand() % 10 > 7)
        {
            x = n1;
            n1 = n2;
            n2 = x;
        }
       if ((tmp = p->get_ass(Chanel::hash("_val"), false)))
       {
           if (tmp->get_value()._ui == Chanel::hash("_choice"))
           {
               res->set_key(n1->get_key());
               if (n1->get_key() != n2->get_key())
                    n1->copy(res);
               else if (n1->get_key())
                    res = cross(n1, n2, p->get_ass(Chanel::hash("_choice"))->get_ass(n1->get_key()).get());
               else if (!n1->get_son().size())
                    n1->copy(res);
               else
               {
                    res->get_value() = n1->get_value();
                    res->set_type(n1->get_type());
               }
           }
           else
           {
                res->set_key(n1->get_key());
                res->get_value() = n1->get_value();
                res->set_type(n1->get_type());
           }
       }
       else
       {
           res->set_key(n1->get_key());
           res->get_value() = n1->get_value();
           res->set_type(n1->get_type());
       }
       if ((tmp = p->get_ass(Chanel::hash("_son"), false)))
       {
            for (unsigned int it = 0; it < n1->get_son().size(); it++)
            {
                if (n2->get_son().size() > it)
                    res->add_son(cross(n1->get_son_ref(it).get(), n2->get_son_ref(it).get(), tmp.get()));
                else if (rand() % 100 > 40)
                    res->add_son(n1->get_son_ref(it)->copy());
            }
       }
    }
    else
    {
        res->get_value() = n1->get_value();
        res->set_type(n1->get_type());
        for (unsigned int it = 0; it < n1->get_son().size(); it++)
        {
            if (n2->get_son().size() > it)
                res->add_son(cross(n1->get_son_ref(it).get(), n2->get_son_ref(it).get(), p->get_son_ref(it).get()));
        }
    }
    return (res);
}

float           Individu::getScore()
{
    return (m_score);
}

void            Individu::evaluate()
{
    std::string com;
    std::stringstream  str;
    FILE        *res;
    char        rd[20];
    int         r;

    com = "./testdna.sh ";
    com += m_file;
    res = popen(com.c_str(), "r");
    r = read(fileno(res), rd, 19);
    if (r != -1)
    {
        rd[r] = 0;
        str << rd;
        str >> m_score;
        if (!m_score)
            m_score = -1000;
    }
    pclose(res);
    m_calculate = true;
}

bool            Individu::getCalculate()
{
    return (m_calculate);
}
