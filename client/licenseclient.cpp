#include "licenseclient.h"

LicenseClient::LicenseClient(unsigned int s, unsigned int f)
{
    li.l1.pid.product = PRODUCT_ID;
    li.l1.pid.version = PRODUCT_VER;
    li.l1.pid.serial = s;
    li.l1.pid.features = f;
    li.l1.uid.collect();
    li.l1.pid.calc_exe();
    li.l1.fill();
    li.l2.fill();
    li.l3.calc_hash(li.l1, li.l2);
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

