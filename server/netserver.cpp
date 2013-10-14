#include "netserver.h"
#include <QDebug>

NetServer::NetServer(QObject *parent) :
    NetObject(SERVER_PORT, parent)
{
}

void NetServer::processTheDatagram(QByteArray &datagram, QHostAddress &sender, quint16 senderPort)
{
    string data = HexUtil::toHex((byte*)datagram.data(), datagram.size());
    qDebug() << sender << senderPort << data.c_str();
}

void NetServer::timerTimeout()
{
    QByteArray data;
    QHostAddress host;
    quint16 port;

    data = "100";
    host = QHostAddress::Broadcast;
    port = CLIENT_PORT;

    udp.writeDatagram(data, host, port);
}
