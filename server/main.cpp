#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    License lic;

    UniqueID uid;
    string hash1;
    byte* h1;
    int len;
    cout << "Hash 1: ";
    cin >> hash1;
    lic.fromHex(hash1, h1, len);
    memcpy(uid.hash1, h1, len);

    lic.setUID(uid);

    cout << "Finding a valid license..." << endl;
    cout << "License: " <<lic.generateLicense1() << endl;


    return a.exec();
}
