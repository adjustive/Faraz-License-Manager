#ifndef PRODUCTID_H
#define PRODUCTID_H

struct ProductID
{
    unsigned short int product;
    unsigned short int version;

    unsigned int serial;

    unsigned int features1;
    unsigned int features2;

    char executable_addr[512];
    char executable_hash[HASH_ALGO::DIGESTSIZE];
};

#endif // PRODUCTID_H
