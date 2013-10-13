#ifndef RSAUTIL_H
#define RSAUTIL_H

#include <iostream>
#include <string>
#include <vector>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/sha3.h>
#include <cryptopp/md5.h>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>
#include <cryptopp/pssr.h>
#include <cryptopp/secblock.h>
#include <cryptopp/files.h>

#include "hexutil.h"

#define KEY_SIZE 4096

class RSAUtil
{
public:
    RSAUtil();

    static void RsaGenerateStringKeys(std::string & publicKeyStr, std::string & privateKeyStr);
    static void RsaSignVector(const std::string & privateKeyStrHex, const std::vector<char> & vec, std::string & sign);
    static bool RsaVerifyVector(const std::string & publicKeyStrHex, const std::string& source, const std::vector<char>& sign);
};

#endif // RSAUTIL_H
