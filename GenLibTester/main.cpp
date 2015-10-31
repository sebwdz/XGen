
#include    "include/BrainView.hpp"
#include    "../GenLib/include/Cell/Brain.hpp"

void        exec(Brain *brain, BrainView *view)
{
  sf::Event event;
  int      cycle;
  int      min = 0;
  int     all = 0;
  float   tall = 0;
  float   last = 0;
  float     t;
  float   prev[2] = {0};
  struct timeval      _time[2];

  cycle = 0;
  Monitor::get_instance()->begin_time(MN_ALL);
  gettimeofday(&_time[0], NULL);
  while ((!view && cycle < 3000) || (view && view->isOpen()))
  {
      if (view && view->isOpen() && !(cycle % 5))
        {
          brain->make_skeleton();
          view->show_tester(brain);
        }
      if (view && view->isOpen())
        {
          if (view->pollEvent(event))
             {
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Escape)
                    {
                        view->close();
                    }
                }
            }
        }
      brain->exec();
      cycle++;
      if (!(cycle % 100))
      {
          gettimeofday(&_time[1], NULL);
          last = 100.0 / (float)((_time[1].tv_sec + _time[1].tv_usec / 1000000.0) - (_time[0].tv_sec + _time[0].tv_usec / 1000000.0));
          tall += Monitor::get_instance()->get_time(MN_INSTR);
          prev[0] = Monitor::get_instance()->get_val(MN_INSTR);
          prev[1] = Monitor::get_instance()->get_time(MN_INSTR);
          if (min == 0 || min > 100.0 / (float)((_time[1].tv_sec + _time[1].tv_usec / 1000000.0) - (_time[0].tv_sec + _time[0].tv_usec / 1000000.0)))
              min = 100.0 / (float)((_time[1].tv_sec + _time[1].tv_usec / 1000000.0) - (_time[0].tv_sec + _time[0].tv_usec / 1000000.0));

          t = (_time[1].tv_sec + _time[1].tv_usec / 1000000.0) - (_time[0].tv_sec + _time[0].tv_usec / 1000000.0);
          gettimeofday(&_time[0], NULL);
          std::cout << "\r" << 100 / t << " c/s | " << Monitor::get_instance()->get_val(MN_INSTR) / (t * 1000) << " instr/s  " << std::flush;
          all += Monitor::get_instance()->get_val(MN_INSTR);
          Monitor::get_instance()->reset_val(MN_INSTR);
      }
  }
  Monitor::get_instance()->end_time(MN_ALL);
  std::cout << "\rlast " << last << " c/s   " << prev[0] / 100 << " instrs/c     " <<
               ( prev[0] ) / ( prev[1] * 1000 ) << " * 10⁶ instrs/s" << " real : " << (prev[0] / ( t * 1000 )) << " * 10³ instrs/s" << std::endl;
  std::cout << "Average : " << cycle / (Monitor::get_instance()->get_time(MN_ALL) / 1000) << " c/s" << std::endl;
  std::cout << "Min : " << min  << " c/s" << std::endl;
  std::cout << all / 1000.0  << " * 10³ instrs" << std::endl;
  std::cout << "total time = " << Monitor::get_instance()->get_time(MN_ALL) / 1000 << " s " << std::endl;
  std::cout << "average : " << all / (Monitor::get_instance()->get_time(MN_ALL) * 1000) << " * 10⁶ instrs/s" << std::endl;
  std::cout << "time in instrs = " << tall / 1000 << " s " << std::endl;
  std::cout << "average : " << all / (tall * 1000) << " * 10⁶ instrs/s" << std::endl;
}

int         main(int ac, char **av)
{
  Brain         *brain;
  SMART(GeneticBlock) dna;
  std::string   file;
  BrainView     *view = NULL;

  /*if (ac < 2)
    {
      std::cout << "./GenLibTester node_file" << std::endl;
      return (1);
    }*/
  if (ac > 2)
    view = new BrainView();
  brain = new Brain();
  dna = SMART(GeneticBlock)(new GeneticBlock());
  file = "../testlib2/out.gen"/*av[1]*/;

  dna->load_file(file);
  brain->set_dna(dna);

  exec(brain, view);

  delete brain;
  if (view)
    view->close();
  delete view;
  return (0);
}
