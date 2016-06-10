
#include            "Decriptor/Opt.hpp"
#include            "Decriptor/DecriptorManager.hpp"

DecriptorManager::DecriptorManager()
{
  m_opt.insert(std::make_pair(SET, &Decriptor::set_function));
  m_opt.insert(std::make_pair(ADD, &Decriptor::set_function));
  m_opt.insert(std::make_pair(SUB, &Decriptor::set_function));
  m_opt.insert(std::make_pair(MULT, &Decriptor::set_function));
  m_opt.insert(std::make_pair(DIV, &Decriptor::set_function));
  m_opt.insert(std::make_pair(MOD, &Decriptor::set_function));
  m_opt.insert(std::make_pair(SUP, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(INF, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(EGAL, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(OR, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(AND, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(XOR, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(NO, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(WHILE, &Decriptor::loop));
  m_opt.insert(std::make_pair(CREAT, &Decriptor::creat_function));
  m_opt.insert(std::make_pair(DETACH, &Decriptor::creat_function));
  m_opt.insert(std::make_pair(NEW_HEAD, &Decriptor::creat_function));
  m_opt.insert(std::make_pair(SHARED, &Decriptor::use_function));
  m_opt.insert(std::make_pair(UNSHARED, &Decriptor::use_function));
  m_opt.insert(std::make_pair(FREE, &Decriptor::decript_function));
  m_opt.insert(std::make_pair(DUPLIC, &Decriptor::creat_function));
  m_opt.insert(std::make_pair(KILL, &Decriptor::decript_function));
  m_opt.insert(std::make_pair(TAKEOUT, &Decriptor::decript_function));
  m_opt.insert(std::make_pair(SPLIT, &Decriptor::decript_function));
  m_opt.insert(std::make_pair(SPLITIN, &Decriptor::decript_function));
  m_opt.insert(std::make_pair(ECHO, &Decriptor::echo));
  m_opt.insert(std::make_pair(COPY, &Decriptor::copy));
  m_opt.insert(std::make_pair(CALL, &Decriptor::call));
  m_opt.insert(std::make_pair(DEREF, &Decriptor::ref_function));
  m_opt.insert(std::make_pair(REF, &Decriptor::ref_function));
  m_opt.insert(std::make_pair(SIZE, &Decriptor::node_size));
  m_opt.insert(std::make_pair(RETURN, &Decriptor::ret));
  m_opt.insert(std::make_pair(POW, &Decriptor::pow));
  m_opt.insert(std::make_pair(RAND, &Decriptor::rand));
  m_opt.insert(std::make_pair(ERASE, &Decriptor::erase));
  m_opt.insert(std::make_pair(MOVE, &Decriptor::move_pos));
  m_opt.insert(std::make_pair(ROUND, &Decriptor::round));
  m_opt.insert(std::make_pair(SQRT, &Decriptor::sqrt));
  m_opt.insert(std::make_pair(KEY_EXIST, &Decriptor::key_exist));
  m_opt.insert(std::make_pair(ATTACH_INSTRU, &Decriptor::attach));
  m_opt.insert(std::make_pair(FREE, &Decriptor::free));
  m_opt.insert(std::make_pair(INCR, &Decriptor::incr));
  m_opt.insert(std::make_pair(DECR, &Decriptor::incr));
  m_opt.insert(std::make_pair(VAL, &Decriptor::val));
  m_opt.insert(std::make_pair(CP_ONE, &Decriptor::copy_one));
  m_opt.insert(std::make_pair(NIL_INSTRU, &Decriptor::nothing));
  m_opt.insert(std::make_pair(MATCH, &Decriptor::match));
}

DecriptorManager::~DecriptorManager()
{

}

DecriptorManager    *DecriptorManager::get_instance()
{
  static DecriptorManager inst;

  return (&inst);
}

SMART(GeneticalNode)    (Decriptor::*DecriptorManager::get_function(GeneticalNode* node))(GeneticalNode*)
{
  if (node->get_type() == INSTRU)
    {
      if (m_opt.find(node->get_value()._uc) != m_opt.end())
        return (m_opt.at(node->get_value()._uc));
    }
  return (&Decriptor::nothing);
}
