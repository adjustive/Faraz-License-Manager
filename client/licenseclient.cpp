#include "licenseclient.h"

LicenseClient::LicenseClient()
{
}

LicenseClient* LicenseClient::instance()
{
    static LicenseClient lc;
    return &lc;
}

void LicenseClient::update()
{
    li.l2.update();
    li.l3.update(li.l1, li.l2);
}

void LicenseClient::init(unsigned int s, unsigned int f)
{
    li.l1.pid.product = PRODUCT_ID;
    li.l1.pid.version = PRODUCT_VER;
    li.l1.pid.serial = s;
    li.l1.pid.features = f;
    update();
}

int LicenseClient::setKey1(string key1)
{
    vector<byte> vk1;
    vk1 = HexUtil::fromHex(key1);
    int min = LI_SIZE < vk1.size() ? LI_SIZE : vk1.size();
    memcpy(li.key1, vk1.data(), min);
    memset(li.key1+min, 0, LI_SIZE - min);
    return License::checkLicense1(vk1, li);
}

int LicenseClient::getFeature(unsigned int f)
{
    return 0;
}

LicenseInfo LicenseClient::getLicenseInfo()
{
    return li;
}

void LicenseClient::printLicenseInfo()
{
    li.l1.print();
    li.l2.print();
    li.l3.print();
}

int LicenseClient::checkLicense2()
{
    //encrypt lInfo with the public key and send it to the server.
    //server opens it with the private key
    //server checks the licence, exe hash, ...
    //
    string pub = PUBLIC_KEY;

    return 0;
}

