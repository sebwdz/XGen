
#include                <iostream>
#include                "Test.hpp"

Test::Test(const std::vector<bool> &in, const std::vector<bool> &out) : m_input(in), m_output(out)
{

}

void            Test::apply(SMART(GeneticalNode) in)
{
    SMART(GeneticalNode)        tmp;
    static int t = 0;
    if (t++ > 5)
    {
        t = 0;
        for (unsigned int i = 0; i < in->get_ass(Chanel::hash("_data"))->get_son().size(); i++)
        {
            if (i >= m_input.size())
                break;
            tmp = boost::static_pointer_cast<GeneticalNode>(in->get_ass(Chanel::hash("_data"))->get_son_ref(i)->get_ref());
            if (m_input[i])
                tmp->get_ass(Chanel::hash("Impulse"))->get_value()._f = 10;
            else
                tmp->get_ass(Chanel::hash("Impulse"))->get_value()._f = 0;
        }
    }
}

bool            Test::evaluate(int active)
{
    SMART(GeneticalNode)    tmp;

    for (unsigned int i = 0; i < m_output.size(); i++)
    {
        if (m_output[i] && active >= 10)
            return (true);
        else if (!m_output[i] && active < 10)
            return (true);
    }
    return (false);
}

void            Test::print()
{
    std::cout << "{ ";
    for (unsigned int it = 0; it < m_input.size(); it++)
        std::cout << m_input[it] << ", ";
    std::cout << "}" << "{ ";
    for (unsigned int it = 0; it < m_output.size(); it++)
        std::cout << m_output[it] << ", ";
    std::cout << "}" << std::endl;
}
