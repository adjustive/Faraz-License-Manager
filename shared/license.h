#ifndef LICENSE_H
#define LICENSE_H

#include "cryptopp.h"
#include "hardwareuid.h"
#include "productid.h"

#define HASH_ALGO SHA3_256
#define ZERO_BYTES 3
#define LI_SIZE 16
#define SALT_1 "12345678901234567890123456789012"
#define SALT_2 "12345678901234567890123456789012"

struct LicenseInfo_1
{
    HardwareUID uid;
    ProductID pid;

    byte salt[32];
    byte random[32];

    LicenseInfo_1()
    {
        memset(salt, 0, 32);
        memset(random, 0, 32);
    }

    void fill_salt()
    {
        memcpy(salt, SALT_1, 32);
    }

    void fill_random()
    {
        AutoSeededRandomPool rng;
        rng.GenerateBlock(random, 32);
    }

    void print()
    {
        uid.print();
        pid.print();
        cout << "Salt   = " << HexUtil::toHex(salt  , 32) << endl;
        cout << "Random = " << HexUtil::toHex(random, 32) << endl;
    }
};

struct LicenseInfo_2
{
    byte hash1[HASH_ALGO::DIGESTSIZE];
    byte hash2[HASH_ALGO::DIGESTSIZE];

    void calc_hash(LicenseInfo_1 l1)
    {
        HASH_ALGO hash;
        hash.CalculateDigest(hash1, (byte*)&l1, sizeof(l1) - 38); // FIXME 32
        hash.CalculateDigest(hash2, (byte*)&l1, sizeof(l1));
    }

    void print()
    {
        cout << "Hash1  = " << HexUtil::toHex(hash1, HASH_ALGO::DIGESTSIZE) << endl;
        cout << "Hash2  = " << HexUtil::toHex(hash2, HASH_ALGO::DIGESTSIZE) << endl;
    }
};

struct LicenseInfo
{
    LicenseInfo_1 l1;
    LicenseInfo_2 l2;
    byte license_key[LI_SIZE];
};

class License
{
public:
    License();
    static int checkLicense1(vector<byte> license, LicenseInfo li);
    static int checkLicense1(string license, LicenseInfo li);
};

#endif // LICENSE_H
