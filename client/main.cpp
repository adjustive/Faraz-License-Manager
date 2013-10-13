#include <QCoreApplication>
#include <iostream>
#include "licenseclient.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    unsigned int s, f;
    cout << "Serial Number: ";
    cin >> s;
    cout << "Requested Features: ";
    cin >> f;

    LicenseClient lc(s, f);
    lc.printLicenseInfo();

    string userLicense;
    cout << "Enter License: ";
    cin >> userLicense;

    cout << License::checkLicense1(userLicense, lc.getLicenseInfo()) << endl;
    cout << lc.checkLicense2() << endl;

    return a.exec();
}
