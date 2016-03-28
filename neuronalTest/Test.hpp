#ifndef TEST_HPP
#define TEST_HPP

#include    "Cell/CellClass.hpp"
#include    "Decriptor/Decriptor.hpp"
#include    "Cell/Brain.hpp"

class           Test
{
public:
    Test(std::vector<bool> const&, std::vector<bool> const&);
    ~Test();

    bool        evaluate(int active);
    void        apply(SMART(GeneticalNode) in);
    void        print();

private:
    std::vector<bool>   m_input;
    std::vector<bool>   m_output;
};

#endif // TEST_HPP
