
#include    "include/BrainView.hpp"
#include    "../GenLib/include/Decriptor/Decriptor.hpp"
#include    "../GenLib/include/Cell/Brain.hpp"

std::vector<ModuleClass*> act;
std::vector<ModuleClass*> sens;

void        exec(Brain *brain)
{
  int      cycle;
  int      min = 0;
  int     all = 0;
  float   tall = 0;
  float   last = 0;
  float     t = 0;
  float   prev[2] = {0};
  struct timeval      _time[2];

  cycle = 0;
  Monitor::get_instance()->begin_time(MN_ALL);
  gettimeofday(&_time[0], NULL);
  while (cycle < 1000)
  {
      brain->exec();
      cycle++;
      //continue;
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

nodeValue   toNodeValue(float x)
{
  nodeValue val;
  val._f = x;
  return (val);
}

void        exec_view(Brain *brain)
{
  BrainView *view;
  sf::Event event;
  sf::Clock show[2];
  sf::Clock speedclock[2];
  sf::Clock response;
  sf::Time  time;
  float     sleep;
  unsigned int cycle = 0;
  unsigned int crep = 0;
  unsigned int prev[2] = {0};

  sleep = 0.007;
  view = new BrainView();
  while (view->isOpen())
    {
      if (view->pollEvent(event))
         {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    view->close();
                // stimulie
                if (event.key.code == sf::Keyboard::A)
                  act[0]->get_line()->get_chan(Chanel::hash("Impulse"))->set_value(toNodeValue(60));
                if (event.key.code == sf::Keyboard::Z)
                  act[1]->get_line()->get_chan(Chanel::hash("Impulse"))->set_value(toNodeValue(60));
                if (event.key.code == sf::Keyboard::E)
                  act[2]->get_line()->get_chan(Chanel::hash("Impulse"))->set_value(toNodeValue(60));
                if (event.key.code == sf::Keyboard::K)
                  sens[0]->get_line()->get_chan(Chanel::hash("Impulse"))->set_value(toNodeValue(60));
                if (event.key.code == sf::Keyboard::L)
                  sens[1]->get_line()->get_chan(Chanel::hash("Impulse"))->set_value(toNodeValue(60));
                if (event.key.code == sf::Keyboard::M)
                  sens[2]->get_line()->get_chan(Chanel::hash("Impulse"))->set_value(toNodeValue(60));
                crep = 0;
                response.restart();
            }
        }

      time = show[0].getElapsedTime();
      if (time.asMilliseconds() / 1000.0 >= 24 / 1000.0)
        {
          show[0].restart();
          brain->make_skeleton();
          view->show_tester(brain);
        }
      time = show[1].getElapsedTime();
      if (time.asSeconds() >= 1)
        {
          std::cout << "\r\r" << cycle << " " << (cycle - prev[0]) / (time.asMilliseconds() / 1000.0) << " c/s    " << ((sleep * 1000) * (cycle - prev[0])) / 10 << "% sleep        " << std::flush;
          prev[0] = cycle;
          show[1].restart();
        }
      //usleep((sleep * 1000) * 1000);
      time = speedclock[0].getElapsedTime();
      if (time.asMicroseconds() / 1000000.0 >= sleep)
        {
          speedclock[0].restart();
          brain->exec();/*
          if (sens[0]->get_line()->get_chan(Chanel::hash("ActImpulse"))->get_value()._f > 0 ||
                sens[1]->get_line()->get_chan(Chanel::hash("ActImpulse"))->get_value()._f > 0 ||
                sens[2]->get_line()->get_chan(Chanel::hash("ActImpulse"))->get_value()._f > 0) {
              std::cout << sens[0]->get_line()->get_chan(Chanel::hash("ActImpulse"))->get_value()._f << " " <<
              sens[1]->get_line()->get_chan(Chanel::hash("ActImpulse"))->get_value()._f << " " <<
              sens[2]->get_line()->get_chan(Chanel::hash("ActImpulse"))->get_value()._f << std::endl;
              std::cout << response.getElapsedTime().asMilliseconds() << " " << crep << std::endl;
            }*/
          if (sens[0]->get_line()->get_chan(Chanel::hash("ActImpulse"))->get_value()._f > 0)
              std::cout << "K" << "\t" << sens[0]->get_line()->get_chan(Chanel::hash("ActImpulse"))->get_value()._f << std::endl;
          if (sens[1]->get_line()->get_chan(Chanel::hash("ActImpulse"))->get_value()._f > 0)
              std::cout << "L" << std::endl;
          if (sens[2]->get_line()->get_chan(Chanel::hash("ActImpulse"))->get_value()._f > 0)
              std::cout << "M" << std::endl;
          crep++;
          cycle++;
        }
      if (cycle - prev[1] > 25)
        {//0.00907
          time = speedclock[1].getElapsedTime();
          sleep = (sleep + 0.00907 - ((time.asMicroseconds() / 1000000.0) / 25.0)) / 2;
          speedclock[1].restart();
          prev[1] = cycle;
          if (sleep < 0)
            sleep = 0;
        }
    }
}

void                  add_act(Brain *brain, std::pair<float, float> pos, bool sensor = false)
{
  static SMART(GeneticalNode) dnaact;
  Decriptor           *decriptor;
  ModuleClass         *module;
  std::string         file;
  nodeValue           value;

  if (!dnaact)
    {
      dnaact = SMART(GeneticalNode)(new GeneticalNode);
      file = "../testlib3/test.gen";
      dnaact->load_file(file);
    }
  decriptor = new Decriptor(NULL);
  decriptor->set_block(dnaact->copy());
  module = new ModuleClass();
  module->attach_decriptor(decriptor);
  module->set_pos(pos);
  value._f = 200;
  if (sensor) {
      module->get_line()->get_chan(Chanel::hash("IM_SENSOR"))->set_value(value);
      sens.push_back(module);
    }
  else
  {
    module->get_line()->get_chan(Chanel::hash("IM_ACTOR"))->set_value(value);
    act.push_back(module);
  }
  brain->add_object(module);
}

int         main(int ac, char **av)
{
  Brain         *brain;
  SMART(GeneticalNode) dna;
  std::string   file;

  if (ac < 2)
    {
      std::cout << "./GenLibTester node_file" << std::endl;
      return (1);
    }
  brain = new Brain();
  dna = SMART(GeneticalNode)(new GeneticalNode());
  file = av[1];
  dna->load_file(file);
  brain->set_dna(dna);

      add_act(brain, std::make_pair(50.0, -50.0));
      add_act(brain, std::make_pair(50.0, 0.0));
      add_act(brain, std::make_pair(50.0, 50.0));

      add_act(brain, std::make_pair(-50.0, -50.0), true);
      add_act(brain, std::make_pair(-50.0, 0.0), true);
      add_act(brain, std::make_pair(-50.0, 50.0), true);

  if (ac > 2)
    exec_view(brain);
  else
    exec(brain);

  delete brain;
  return (0);
}
