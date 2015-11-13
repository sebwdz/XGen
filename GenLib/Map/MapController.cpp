
#include            "Map/MapController.hpp"

MapController::MapController()
{
  m_map = new ClassMap();
  m_map->set_size(250);
}


MapController::~MapController()
{
  delete m_map;
}

void            MapController::add_obj(Object *obj)
{
  m_map->add_obj(obj);
}

void            MapController::move_object(Object *obj)
{
  std::pair<int, int>       pos;
  std::pair<int, int>   tmp;

  tmp = obj->get_cases()->get_lnk()->get_pos();
  pos = obj->get_pos();
  pos.first += pos.first < 0 ? -m_map->get_size() / 10 : m_map->get_size() / 10;
  pos.second += pos.second < 0 ? -m_map->get_size() / 10  : m_map->get_size() / 10;
  pos.first = pos.first / (m_map->get_size() / 5);
  pos.second = pos.second / (m_map->get_size() / 5);
  if (tmp.first != pos.first ||
      tmp.second != pos.second)
    {
      remove_object(obj);
      add_obj(obj);
    }
}

void MapController::remove_object(Object *obj)
{
  m_map->remove_object(obj);
}


ClassMap                        *MapController::get_map()
{
  return (m_map);
}
