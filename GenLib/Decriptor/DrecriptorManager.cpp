
#include            "Decriptor/Opt.hpp"
#include            "Decriptor/DecriptorManager.hpp"

DecriptorManager::DecriptorManager()
{
  m_opt.insert(std::make_pair(SET, &Decriptor::set_function));
  m_opt.insert(std::make_pair(ADD, &Decriptor::set_function));
  m_opt.insert(std::make_pair(SUB, &Decriptor::set_function));
  m_opt.insert(std::make_pair(MULT, &Decriptor::set_function));
  m_opt.insert(std::make_pair(DIV, &Decriptor::set_function));
  m_opt.insert(std::make_pair(SUP, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(INF, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(EGAL, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(OR, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(AND, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(XOR, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(NO, &Decriptor::comp_funcion));
  m_opt.insert(std::make_pair(CREAT, &Decriptor::creat_function));
  m_opt.insert(std::make_pair(DETACH, &Decriptor::creat_function));
  m_opt.insert(std::make_pair(NEW_HEAD, &Decriptor::creat_function));
  m_opt.insert(std::make_pair(USE, &Decriptor::use_function));
  m_opt.insert(std::make_pair(UNUSE, &Decriptor::use_function));
  m_opt.insert(std::make_pair(SHARED, &Decriptor::use_function));
  m_opt.insert(std::make_pair(UNSHARED, &Decriptor::use_function));
  m_opt.insert(std::make_pair(FREE, &Decriptor::decript_function));
  m_opt.insert(std::make_pair(DUPLIC, &Decriptor::creat_function));
  m_opt.insert(std::make_pair(KILL, &Decriptor::decript_function));
  m_opt.insert(std::make_pair(VAR, &Decriptor::set_var_function));
  m_opt.insert(std::make_pair(TAKEOUT, &Decriptor::decript_function));
  m_opt.insert(std::make_pair(SPLIT, &Decriptor::decript_function));
  m_opt.insert(std::make_pair(ECHO, &Decriptor::echo));
}

DecriptorManager::~DecriptorManager()
{

}

DecriptorManager    *DecriptorManager::get_instance()
{
  static DecriptorManager inst;

  return (&inst);
}

int     (Decriptor::*DecriptorManager::get_function(GeneticalNode* node))(GeneticalNode*)
{
  if (node->get_type() == INSTRU)
    {
      if (m_opt.find(node->get_value()._uc) != m_opt.end())
        return (m_opt.at(node->get_value()._uc));
    }
  return (&Decriptor::nothing);
}
