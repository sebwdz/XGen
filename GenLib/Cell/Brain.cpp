
#include        <boost/lexical_cast.hpp>
#include        <ctime>
#include        "include/Cell/CellClass.hpp"
#include        "include/Cell/Brain.hpp"

unsigned int Package::_code = 0;

Brain::Brain() : ModuleClass(NULL)
{
  m_type ^= TYPE_BRAIN;
  Package::_code = random();
}

Brain::~Brain()
{

}

void        Brain::set_dna(boost::shared_ptr<GeneticalNode> block)
{
  CellClass       *cell;
  std::pair<float, float>   p;

  cell = new CellClass(this);
  cell->set_dna(block);
  p.first = 0;
  p.second = 0;
  cell->set_pos(p);
  add_object(cell);
}

void        Brain::exec()
{
    Package     *res;

    static int  t = 0;
    while (m_send.size())
    {
        m_sender.send(m_send.back());
        delete m_send.back();
        m_send.pop_back();
    }
    t++;
    ModuleClass::exec();
    make_move_line();
    move();
    exec_move();
    do {
        res = m_receiver.listen();
        if (res)
        {
            exec_interactions(res);
            delete[] res->data;
            delete res;
        }
    } while (res);
}

void                            Brain::send_interaction(Object* from, GeneticalNode *prop)
{
    Serialize                   data;
    Serialize                   *tmp;
    Package                     *pack;
    SMART(GeneticalNode)        node(new GeneticalNode);
    unsigned int                size;
    char                        *res;

    data.append((char*)&Package::_code, sizeof(unsigned int));
    data.append((char*)"I", sizeof(char));
    tmp = prop->serialize();
    data.append(tmp->data.data(), tmp->data.size());
    delete tmp;
    /*from->get_used(prop, node);
    tmp = node->serialize();
    data.append(tmp->data.data(), tmp->data.size());
    delete tmp;*/
    pack = new Package;
    res = new char[data.data.size()];
    pack->data = (char*)memcpy(res, data.data.data(), data.data.size());
    pack->size = data.data.size();
    m_send.push_back(pack);
}

void                        Brain::exec_interactions(Package *pack)
{
    char                    *data;
    SMART(GeneticalNode)    node(new GeneticalNode());
    SMART(GeneticalNode)    global(new GeneticalNode());

    data = pack->data;
    data += sizeof(unsigned int) + sizeof(char);
    data = node->deserialize(data);
    //data = get_line()->get_chan()->deserialize(data);
    for (unsigned int it = 0; it < m_obj.size(); it++)
    {
        if (m_obj[it]->get_type() & TYPE_MOVABLE)
            m_moveLine.interact_with(CAST(Movable*)(m_obj[it]), node);
    }
}
