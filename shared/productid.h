#ifndef PRODUCTID_H
#define PRODUCTID_H

#include <iostream>
#include "hexutil.h"
#include "cryptopp.h"

#define EXE_HASH_ALGO SHA3_256
//#define EXE_HASH_ALGO MD5

using namespace std;

struct ProductID
{
    unsigned short int product;
    unsigned short int version;

    unsigned int serial;
    unsigned int features;

    char executable_addr[512];
    char executable_hash[EXE_HASH_ALGO::DIGESTSIZE];

    void calc_exe()
    {
        int exelen = readlink("/proc/self/exe", executable_addr, 512);
        memset(executable_addr + exelen, 0, 512 - exelen);

        EXE_HASH_ALGO hash;
        FileSource(executable_addr, true,
                   new HashFilter (hash,
                   new ArraySink((byte*)executable_hash, EXE_HASH_ALGO::DIGESTSIZE))); //LEAK!
    }

    void print()
    {
        cout << "Product  = " << product << endl;
        cout << "Version  = " << version << endl;
        cout << "Serial   = " << serial << endl;
        cout << "Features = " << features << endl;
        cout << "EXE Addr = " << executable_addr << endl;
        cout << "EXE Hash = " << HexUtil::toHex((byte*)executable_hash, EXE_HASH_ALGO::DIGESTSIZE) << endl;
    }
};

#endif // PRODUCTID_H
