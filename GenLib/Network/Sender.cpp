
#include            "Network/Sender.hpp"

Sender::Sender() : QUdpSocket()
{
    m_addr = QHostAddress("224.000.000.1");
}

Sender::~Sender()
{

}

void            Sender::send(Package *package)
{
    writeDatagram(package->data, package->size, m_addr, 12345);
}
