#include "netclient.h"

NetClient::NetClient(QObject *parent) :
    NetObject(CLIENT_PORT, parent)
{
}

void NetClient::processTheDatagram(QByteArray &datagram, QHostAddress &sender, quint16 senderPort)
{

}

void NetClient::timerTimeout()
{

}
