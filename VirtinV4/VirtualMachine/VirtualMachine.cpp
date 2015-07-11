
#include        "VirtualMachine/VirtualMachine.hpp"

VirtualMachine::VirtualMachine()
{
    m_view = 0;
}

VirtualMachine::~VirtualMachine()
{
}

void            VirtualMachine::set_view(MachineView *view)
{
    m_view = view;
}

bool            VirtualMachine::get_start()
{
    return (m_start);
}
