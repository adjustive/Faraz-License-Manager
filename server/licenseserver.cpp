#include "licenseserver.h"

LicenseServer::LicenseServer()
{
}

string LicenseServer::generateLicense1(LicenseInfo li)
{
    byte license[LI_SIZE];
    memset(license, 0, LI_SIZE);
    AutoSeededRandomPool rng;

    bool done = false;
    unsigned int t=20000000;  // TODO
    unsigned int i;
    for(i=0; i<t; i++)
    {
        rng.GenerateBlock(license, LI_SIZE);
        //memcpy(license, &i, 4);
        vector<byte> vl(license, license + LI_SIZE);
        if(License::checkLicense1(vl, li) == ZERO_BYTES)
        {
            done = true;
            break;
        }
    }
    cout << "Tries = " << i << endl;

    if(done) return HexUtil::toHex(license, LI_SIZE);
    else return "FAILED!";
}


