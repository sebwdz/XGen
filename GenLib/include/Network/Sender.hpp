#ifndef SENDER_HPP
#define SENDER_HPP

#include            <QtNetwork/QUdpSocket>
#include            "Package.hpp"

class               Sender : public QUdpSocket
{
public:
    Sender();
    ~Sender();

    void            send(Package *package);
private:
    QHostAddress    m_addr;
};

#endif // SENDER_HPP
