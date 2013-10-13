#ifndef HEXUTIL_H
#define HEXUTIL_H

#include <string>
#include <vector>
#include <cryptopp/hex.h>

using namespace std;
using namespace CryptoPP;

class HexUtil
{
public:
    HexUtil();
    static string toHex(byte* input, int len);
    static vector<byte> fromHex(string input);
};

#endif // HEXUTIL_H
