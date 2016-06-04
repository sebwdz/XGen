
#include            <iostream>
#include            <QtNetwork/QNetworkInterface>
#include            "Network/Receiver.hpp"

Receiver::Receiver() : QUdpSocket()
{
    m_addr = QHostAddress("224.0.0.1");
    bind(QHostAddress::Any, 16325, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        if (interface.name() == "wlan0")
            setMulticastInterface(interface);
    }
    joinMulticastGroup(m_addr);
}

Receiver::~Receiver()
{

}

Package         *Receiver::listen()
{
    Package     *package;

    if (hasPendingDatagrams())
    {
        package = new Package;
        package->size = pendingDatagramSize();
        package->data = new char[package->size + 1];
        readDatagram(package->data, package->size, &package->host);
        package->data[package->size] = 0;
        if (*((unsigned int*)package->data) != Package::_code)
            return (package);
        delete[] package->data;
        delete package;
    }
    return (NULL);
}
