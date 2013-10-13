#include <QCoreApplication>
#include <iostream>

#include "hexutil.h"
#include "rsautil.h"

using namespace std;

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    cout << "Hex Util :" << endl;
    vector<byte> b1;
    string s1, s2;
    s1 = "12:34:AB:CD:FF";
    b1 = HexUtil::fromHex(s1);
    s2 = HexUtil::toHex(b1.data(), b1.size());
    cout << s1 << endl << b1.size() << endl << s2 << endl;

    cout << "\n--------------------\n\n";

    cout << "RSA Util :" << endl;
    string public_key, private_key;
    RSAUtil::RsaGenerateStringKeys(public_key, private_key);
    cout << "public_key :" << endl << public_key << endl;
    cout << "private_key :" << endl << private_key << endl;




    return 0;
    //return a.exec();
}
