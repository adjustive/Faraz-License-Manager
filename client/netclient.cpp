#include "netclient.h"
#include "licenseclient.h"
#include <QDebug>

NetClient::NetClient(QObject *parent) :
    NetObject(CLIENT_PORT, parent)
{
}

void NetClient::processTheDatagram(QByteArray &datagram, QHostAddress &sender, quint16 senderPort)
{
    string data = HexUtil::toHex((byte*)datagram.data(), datagram.size());
    qDebug() << sender << senderPort << data.c_str();
}

void NetClient::timerTimeout()
{
    static unsigned short int counter = 0; counter++;
    LicenseClient* lc = LicenseClient::instance();
    int mod = counter % 5;
    QByteArray data;
    QHostAddress host;
    quint16 port;
    bool send = false;

    vector<byte> key1 = lc->getLicenseInfo().key1;

    switch (mod)
    {
    case 0: // Send multicast to clients
    {
        data.append("000\n");
        data.append((const char*)key1.data(), key1.size());
        host = QHostAddress(MULTICAST_GROUP);
        port = CLIENT_PORT;
        send = true;
        break;
    }

    case 1: // Send broadcast to clients
    {
        data.append("001\n");
        data.append((const char*)key1.data(), key1.size());
        host = QHostAddress::Broadcast;
        port = CLIENT_PORT;
        send = true;
        break;
    }
    case 2: // Send multicast to servers
    {
        data.append("002\n");
        host = QHostAddress(MULTICAST_GROUP);
        port = SERVER_PORT;
        send = true;
        break;
    }
    case 3: // Send broadcast to servers
    {
        data.append("003\n");
        host = QHostAddress::Broadcast;
        port = SERVER_PORT;
        send = true;
        break;
    }

        // TODO : NET SERVER

    default: // Update license
    {
        lc->update();
        break;
    }
    }

    if(send) udp.writeDatagram(data, host, port);
}
