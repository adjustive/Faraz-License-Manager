#ifndef NETCLIENT_H
#define NETCLIENT_H

#include "netobject.h"

class NetClient : public NetObject
{
    Q_OBJECT
public:
    explicit NetClient(QObject *parent = 0);

private:
    virtual void processTheDatagram(QByteArray &datagram, QHostAddress &sender, quint16 senderPort);

signals:

public slots:

private slots:
    virtual void timerTimeout();
};

#endif // NETCLIENT_H
