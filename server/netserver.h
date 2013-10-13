#ifndef NETSERVER_H
#define NETSERVER_H

#include "netobject.h"

class NetServer : public NetObject
{
    Q_OBJECT
public:
    explicit NetServer(QObject *parent = 0);

private:
    virtual void processTheDatagram(QByteArray &datagram, QHostAddress &sender, quint16 senderPort);

signals:

public slots:

private slots:
    virtual void timerTimeout();
};

#endif // NETSERVER_H
