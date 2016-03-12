#ifndef PACKAGE_HPP
#define PACKAGE_HPP

#include            <QtNetwork/QUdpSocket>

class              Package
{
public:
    char                *data;
    unsigned int        size;
    QHostAddress        host;
    static unsigned int _code;
};

#endif // PACKAGE_HPP
