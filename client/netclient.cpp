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
    qDebug() << sender.toString() << senderPort << data.c_str();
    string code = "000";
    memcpy((void*)code.c_str(), datagram.data(), 3);
    //qDebug() << "Code" << code.c_str();
    if(code == "001" || code == "002")
    {
        unsigned int rid;
        memcpy(&rid, datagram.data()+3, sizeof(rid));
        //qDebug() << rid;
        if(rid != rand_id)
        {
            vector<byte> k1;
            int k1size = datagram.size() - (3+4);
            k1.resize(k1size);
            memcpy(k1.data(), datagram.data()+3+4, k1size);

            byte * b2 = LicenseClient::instance()->getLicenseInfo().key1;
            vector<byte> k2;
            k2.resize(LI_SIZE);
            memcpy(k2.data(), b2, LI_SIZE);

            if(k1 == k2) qDebug() << "!!!";
        }
    }
}

void NetClient::timerTimeout()
{
    rand_id = rand();
    static unsigned short int counter = 0; counter++;
    LicenseClient* lc = LicenseClient::instance();
    int mod = counter % 5;
    QByteArray data;
    QHostAddress host;
    quint16 port;
    bool send = false;

    LicenseInfo li = lc->getLicenseInfo();

    switch (mod)
    {
    case 0: // Send multicast to clients
    {
        data.append("001");
        data.append((const char*)&rand_id, sizeof(rand_id));
        data.append((const char*)li.key1, LI_SIZE);
        host = QHostAddress(MULTICAST_GROUP);
        port = CLIENT_PORT;
        send = true;
        break;
    }

    case 1: // Send broadcast to clients
    {
        data.append("002");
        data.append((const char*)&rand_id, sizeof(rand_id));
        data.append((const char*)li.key1, LI_SIZE);
        host = QHostAddress::Broadcast;
        port = CLIENT_PORT;
        send = true;
        break;
    }
    case 2: // Send multicast to servers
    {
        data.append("003");
        data.append((const char*)&li, sizeof(li));
        host = QHostAddress(MULTICAST_GROUP);
        port = SERVER_PORT;
        send = true;
        break;
    }
    case 3: // Send broadcast to servers
    {
        data.append("004");
        data.append((const char*)&li, sizeof(li));
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
