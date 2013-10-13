#include "license.h"

License::License()
{
}

int License::checkLicense1(vector<byte> license, LicenseInfo li)
{
    // assert(size == LI_SIZE);

    int buffer_size = HASH_ALGO::DIGESTSIZE + license.size() + 32;
    byte* buffer = new byte[buffer_size];
    memcpy(buffer, &li.l3.hash1, HASH_ALGO::DIGESTSIZE);
    memcpy(buffer + HASH_ALGO::DIGESTSIZE, license.data(), license.size());
    memcpy(buffer + buffer_size - 32, SALT_2, 32);

    //cout<< "MERGED    = " <<  toHex(buffer,buffer_size) << endl;

    HASH_ALGO hash;
    byte digest[HASH_ALGO::DIGESTSIZE];
    hash.CalculateDigest(digest, buffer, buffer_size);

    //cout<< "HASHED    = " <<  toHex(digest,HASH_ALGO::DIGESTSIZE) << endl;

    int flag=0;
    for(int i=0; i<ZERO_BYTES; i++)
        if(digest[i] == 0 ) flag++;

    //if(flag==ZERO_BYTES) cout<< "HASHED    = " <<  toHex(digest,HASH_ALGO::DIGESTSIZE) << endl;

    //memcpy(lInfo.license, license, size);

    delete[] buffer;
    return flag;
}

int License::checkLicense1(string license, LicenseInfo li)
{
    vector<byte> buffer;
    buffer = HexUtil::fromHex(license);
    int res = checkLicense1(buffer, li);
    return res;
}
