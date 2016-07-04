
#include        <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include        "Genetic/GeneticalAorithm.hpp"

int main(int ac, char **av)
{
    SMART(GeneticalNode)    patern(new GeneticalNode());
    int                     cycle = 0;

    if (ac < 3)
    {
        std::cout << "./dna pop_size cycle" << std::endl;
        return (1);
    }
    GeneticAlgorithm        algo;
    srand(time(NULL));
    patern->load_file("dna.gen");
    mkdir("pop",  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    algo.setPatern(patern);
    algo.load();
    algo.generate(atoi(av[1]));
    while (cycle < atoi(av[2]))
    {
        std::cout << "begin cycle" << cycle << std::endl;
        algo.exec(atoi(av[1]));
        cycle++;
    }
    std::cout << std::endl;
    return (0);
}
