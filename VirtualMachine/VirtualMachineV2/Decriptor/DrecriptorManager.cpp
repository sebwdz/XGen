
#include            "Decriptor/Opt.hpp"
#include            "Decriptor/DecriptorManager.hpp"

DecriptorManager::DecriptorManager()
{
    m_opt.insert(std::make_pair(SET, &Decriptor::set_function));
    m_opt.insert(std::make_pair(ADD, &Decriptor::set_function));
    m_opt.insert(std::make_pair(SUB, &Decriptor::set_function));
    m_opt.insert(std::make_pair(SUP, &Decriptor::comp_funcion));
    m_opt.insert(std::make_pair(INF, &Decriptor::comp_funcion));
    m_opt.insert(std::make_pair(EGAL, &Decriptor::comp_funcion));
    m_opt.insert(std::make_pair(CREAT, &Decriptor::creat_function));
    m_opt.insert(std::make_pair(DETACH, &Decriptor::creat_function));
    m_opt.insert(std::make_pair(NEW_HEAD, &Decriptor::creat_function));
    m_opt.insert(std::make_pair(USE, &Decriptor::use_function));
    m_opt.insert(std::make_pair(UNUSE, &Decriptor::use_function));
    m_opt.insert(std::make_pair(SHARED, &Decriptor::use_function));
    m_opt.insert(std::make_pair(UNSHARED, &Decriptor::use_function));
    m_opt.insert(std::make_pair(FREE, &Decriptor::decript_function));
    m_opt.insert(std::make_pair(LINK, &Decriptor::creat_function));
    m_opt.insert(std::make_pair(UNLINK, &Decriptor::creat_function));
    m_opt.insert(std::make_pair(DUPLIC, &Decriptor::creat_function));
    m_opt.insert(std::make_pair(KILL, &Decriptor::decript_function));
    m_opt.insert(std::make_pair(JMP, &Decriptor::jmp_function));
    m_opt.insert(std::make_pair(VAR, &Decriptor::set_var_function));
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
        if (m_opt.find(node->get_value()) != m_opt.end())
            return (m_opt[node->get_value()]);
    }
    return (&Decriptor::nothing);
}
