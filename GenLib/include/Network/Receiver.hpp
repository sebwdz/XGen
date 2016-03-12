#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include            <QtNetwork/QUdpSocket>
#include            "Package.hpp"

class               Receiver : public QUdpSocket
{
public:
    Receiver();
    ~Receiver();

    Package         *listen();

private:
    QHostAddress    m_addr;
};

#endif // RECEIVER_HPP
