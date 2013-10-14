#include <QCoreApplication>
#include <iostream>
#include "licenseserver.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    LicenseServer ls;
    LicenseInfo li;

    string hash1;
    vector<byte> bhash1;
    cout << "Hash 1: ";
    cin >> hash1;
    bhash1 = HexUtil::fromHex(hash1);
    memcpy(li.l3.hash1, bhash1.data(), bhash1.size());

    cout << "Finding a valid license..." << endl;
    //cout << "License: " << ls.generateLicense1(li) << endl;

    return a.exec();
}
