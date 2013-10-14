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

    LicenseClient *lc = LicenseClient::instance();
    lc->init(s, f);
    lc->printLicenseInfo();

    string key1;
    cout << "Enter License: ";
    cin >> key1;
    cout << lc->setKey1(key1) << endl;

    return a.exec();
}
