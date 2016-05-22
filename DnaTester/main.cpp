
#include        <iostream>
#include        "Genetic/GeneticalAorithm.hpp"

int main()
{
    SMART(GeneticalNode)    patern(new GeneticalNode());
    GeneticAlgorithm        algo;
    int                     cycle = 0;

    srand(time(NULL));
    patern->load_file("../DnaTester/dna.gen");
    std::cout << "started" << std::endl;
    algo.setPatern(patern);
    algo.load();
    algo.generate(150);
    while (cycle < 300)
    {
        std::cout << "begin cycle" << cycle << std::endl;
        algo.exec(150);
        cycle++;
    }
    std::cout << std::endl;
    return (0);
}
