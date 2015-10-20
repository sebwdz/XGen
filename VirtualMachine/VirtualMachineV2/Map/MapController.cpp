
#include            "Map/MapController.hpp"

MapController::MapController()
{
    m_map = new ClassMap();
    m_map->set_size(150);
}


MapController::~MapController()
{
    delete m_map;
}

void            MapController::add_obj(Object *obj)
{
    /*if (std::abs(obj->get_pos().first) > m_map->get_size() / 2 ||
            std::abs(obj->get_pos().second) > m_map->get_size() / 2)
    {
        map = new ClassMap();
        map->set_size(m_map->get_size() * 5);
        lnk = map->make_lnk(pos);
        lnk->set_case(m_map);
        for (it = m_map->get_obj().begin(); it != m_map->get_obj().end(); it++)
        {
            tmp = it->get()->get_cases();
            map->ClassCase::add_obj(*it);
            it->get()->set_case(tmp);
        }
        m_map->set_lnk(lnk);
        m_map = map;
    }*/
    m_map->add_obj(obj);
}

void            MapController::move_object(Object *obj)
{
    std::pair<int, int>       pos;
    std::pair<float, float>   tmp;

    pos = obj->get_cases()->get_lnk()->get_pos();
    tmp = obj->get_pos();
    if (tmp.first / obj->get_cases()->get_size() != pos.first ||
        tmp.second / obj->get_cases()->get_size() != pos.second)
      {
        remove_object(obj);
        add_obj(obj);
      }
}

 void MapController::remove_object(Object *obj)
{
    m_map->remove_object(obj);
}

void                            MapController::clean()
{
    m_map->clean();
}

ClassMap                        *MapController::get_map()
{
    return (m_map);
}
