#include "netobject.h"

NetObject::NetObject(quint16 listenPort, QObject *parent) :
    QObject(parent)
{
    udp.bind(QHostAddress::Any, listenPort, QUdpSocket::ReuseAddressHint);
    udp.joinMulticastGroup(QHostAddress(MULTICAST_GROUP));
    connect(&udp, SIGNAL(readyRead()), this, SLOT(readPendingDatagrams()));
    timer.start(TIMER_INTERVAL);
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
}

void NetObject::readPendingDatagrams()
{
    while (udp.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udp.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        udp.readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        processTheDatagram(datagram, sender, senderPort);
    }
}
