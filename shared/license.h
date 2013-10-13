#ifndef LICENSE_H
#define LICENSE_H

#include <sys/time.h>

#include "cryptopp.h"
#include "hardwareuid.h"
#include "productid.h"

#define HASH_ALGO SHA3_256
#define ZERO_BYTES 3
#define LI_SIZE 16

#define SALT_SIZE 32
#define SALT_1 "12345678901234567890123456789012"
#define SALT_2 "12345678901234567890123456789012"
#define SALT_3 "12345678901234567890123456789012"

struct LicenseInfo_1 // I will get upset if these change
{
    HardwareUID uid;
    ProductID pid;
    byte salt[SALT_SIZE];

    LicenseInfo_1()
    {
        memset(salt, 0, SALT_SIZE);
    }

    void fill()
    {
        memcpy(salt, SALT_1, SALT_SIZE);
    }

    void print()
    {
        uid.print();
        pid.print();
        cout << "Salt1  = " << HexUtil::toHex(salt  , SALT_SIZE) << endl;
    }
};

struct LicenseInfo_2 // I will get upset if these DON'T change
{
    byte random[SALT_SIZE];
    timeval time1;
    time_t time2;
    byte salt[SALT_SIZE];

    LicenseInfo_2()
    {
        memset(random, 0, SALT_SIZE);
        memset(salt  , 0, SALT_SIZE);
    }

    void fill()
    {
        memcpy(salt, SALT_2, SALT_SIZE);
        AutoSeededRandomPool rng;
        rng.GenerateBlock(random, SALT_SIZE);
        gettimeofday(&time1, NULL);
        time2 = time(0);
    }

    void print()
    {
        cout << "Random = " << HexUtil::toHex(random, SALT_SIZE) << endl;
        cout << "Time1  = " << HexUtil::toHex((byte*)&time1, sizeof(time1)) << endl;
        cout << "Time2  = " << HexUtil::toHex((byte*)&time2, sizeof(time2)) << endl;
        cout << "Salt2  = " << HexUtil::toHex(salt  , SALT_SIZE) << endl;
    }
};

struct LicenseInfo_3
{
    byte hash1[HASH_ALGO::DIGESTSIZE];
    byte hash2[HASH_ALGO::DIGESTSIZE];
    byte salt[SALT_SIZE];
    byte hash3[HASH_ALGO::DIGESTSIZE];

    void calc_hash(LicenseInfo_1 l1, LicenseInfo_2 l2)
    {
        memcpy(salt, SALT_3, SALT_SIZE);
        HASH_ALGO hash;
        hash.CalculateDigest(hash1, (byte*)&l1, sizeof(l1));
        hash.CalculateDigest(hash2, (byte*)&l2, sizeof(l2));
        hash.CalculateDigest(hash3, (byte*)this, HASH_ALGO::DIGESTSIZE * 2 + SALT_SIZE);
    }

    void print()
    {
        cout << "Hash1  = " << HexUtil::toHex(hash1, HASH_ALGO::DIGESTSIZE) << endl;
        cout << "Hash2  = " << HexUtil::toHex(hash2, HASH_ALGO::DIGESTSIZE) << endl;
        cout << "Salt3  = " << HexUtil::toHex(salt  , SALT_SIZE) << endl;
        cout << "Hash3  = " << HexUtil::toHex(hash3, HASH_ALGO::DIGESTSIZE) << endl;
    }
};

struct LicenseInfo
{
    LicenseInfo_1 l1;
    LicenseInfo_2 l2;
    LicenseInfo_3 l3;
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
