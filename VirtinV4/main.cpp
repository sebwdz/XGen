
#include    <cstdlib>
#include    <unistd.h>
#include    <ctime>
#include    <iostream>

#include    "VirtualMachine/VirtualMachine.hpp"
#include    "GeneticalPool.hpp"

VirtualMachine      *make_engine()
{
    return (new VirtualMachine());
}

int main(int ac, char **av)
{
    GeneticalPool        *pool = new GeneticalPool();
    std::string          file;

    if (ac < 2)
        return (0);
    srand(time(NULL));
    pool->set_engine_maker(&make_engine);
    std::cout << "generate..." << std::endl;
    if (*av[1] == 'l' && av[2])
    {
        file = av[2];
        pool->load_file(file);
    }
    else
    {
        file = av[1];
        pool->get_propriety()->range.push_back(std::make_pair(OPT_RANGE, DUPLIC + OPT_RANGE + 1));
        pool->get_propriety()->range.push_back(std::make_pair(CHANNEL_RANGE, VALUE_RANGE + 1));
        pool->get_propriety()->range.push_back(std::make_pair(VALUE_RANGE, MAX_RANGE + 1));
        pool->set_height(4);
        pool->set_len(4);
        pool->set_pool_len(2);
        pool->set_size(2000);
        pool->make_pool(3);
    }
    std::cout << "start!" << std::endl;
    pool->exec(10, 1);
    std::cout << "save" << std::endl;
    pool->save_file(file);
    return (0);
}
