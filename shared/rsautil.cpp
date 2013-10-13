#include "rsautil.h"

RSAUtil::RSAUtil()
{
}

void RSAUtil::RsaGenerateStringKeys(std::string & publicKeyStr, std::string & privateKeyStr)
{
    // Pseudo Random Number Generator
    CryptoPP::AutoSeededRandomPool rng;

    // Generate Parameters
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, KEY_SIZE);

    CryptoPP::RSA::PrivateKey privateKey(params);
    CryptoPP::RSA::PublicKey publicKey(params);

    CryptoPP::HexEncoder encoder;

    // save public Key
    encoder.Attach( new CryptoPP::StringSink( publicKeyStr ));
    publicKey.Save(encoder);

    // save private Key
    encoder.Attach( new CryptoPP::StringSink( privateKeyStr ));
    privateKey.Save(encoder);
}

void RSAUtil::RsaSignVector(const std::string & privateKeyStrHex, const std::vector<char> & vec, std::string & sign)
{
    // Pseudo Random Number Generator
    CryptoPP::AutoSeededRandomPool rng;
    /*
    // Generate Parameters
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, KEY_SIZE);
    */

    CryptoPP::HexDecoder decoder;
    decoder.Put( (byte*)privateKeyStrHex.c_str(), privateKeyStrHex.size() );
    decoder.MessageEnd();

    CryptoPP::RSA::PrivateKey privateKey; // Private
    privateKey.Load( decoder );


    CryptoPP::RSASS<CryptoPP::PSS, CryptoPP::SHA1>::Signer signer( privateKey );

    size_t length = signer.MaxSignatureLength();
    CryptoPP::SecByteBlock signature( length );

    // Sign message
    signer.SignMessage( rng, (const byte*) vec.at(0), vec.size(), signature );

    sign  = HexUtil::toHex(signature, signature.size());
}

bool RSAUtil::RsaVerifyVector(const std::string & publicKeyStrHex, const std::string& source, const std::vector<char>& sign)
{
    CryptoPP::HexDecoder decoder;
    decoder.Put( (byte*)publicKeyStrHex.c_str(), publicKeyStrHex.size() );
    decoder.MessageEnd();

    CryptoPP::RSA::PublicKey publicKey;
    publicKey.Load( decoder );

    // Verifier object
    CryptoPP::RSASS<CryptoPP::PSS, CryptoPP::SHA1>::Verifier verifier( publicKey );

    std::vector<char> rawSignature;
    std::string signStr(sign.at(0), sign.size());
    // FIXME
    //utils::FromHexString(utils::string2wstring(signStr), &rawSignature);
    // Verify
    const char * pData = (const char *)source.at(0);
    return verifier.VerifyMessage( (const byte*) pData, source.size(), (const byte*) rawSignature.at(0), rawSignature.size() );
}
