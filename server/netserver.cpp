#include "netserver.h"

NetServer::NetServer(QObject *parent) :
    NetObject(SERVER_PORT, parent)
{
}

void NetServer::processTheDatagram(QByteArray &datagram, QHostAddress &sender, quint16 senderPort)
{

}

void NetServer::timerTimeout()
{

}
