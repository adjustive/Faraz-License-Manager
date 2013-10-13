#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    unsigned int s, f;
    cout << "Serial Number: ";
    cin >> s;
    cout << "Requested Features: ";
    cin >> f;

    License lic(s, f);
    lic.printUID(lic.getInitUID());


    string userLicense;
    cout << "Enter License: ";
    cin >> userLicense;

    cout << lic.checkLicense1(userLicense) << endl;
    cout << lic.checkLicense2() << endl;

    return a.exec();
}
