#include "license.h"

License::License()
{
}

License::~License()
{
}

void License::setUID(UniqueID uid)
{
    lInfo.uid = uid;
}


string License::toHex(byte *input, int len) const
{
    HexEncoder encoder;
    string output;
    encoder.Attach(new StringSink(output));
    encoder.Put(input, len);
    encoder.MessageEnd();
    return output;
}

void License::fromHex(string input, byte* &output, int &len) const
{
    HexDecoder decoder;
    output = new byte[input.length()/2]; // TODO: MEMORY LEAK? input.size() =/= len

    decoder.Put((byte*) input.c_str(), input.length());
    decoder.MessageEnd();

    word64 size = decoder.MaxRetrievable();
    if(size)
    {
        decoder.Get(output, size);
        len = size;
    }
    else len = 0;
}

void License::printUID(UniqueID uid) const
{
    cout << "Host id = " << uid.hostid << endl;
    cout << "CPU vendor = " << uid.cpu_vendor << endl;
    cout << "CPU signature = " << uid.cpu_signature << endl;
    cout << "CPU featurebits[0] = " << uid.cpu_featurebits[0] << endl;
    cout << "CPU featurebits[1] = " << uid.cpu_featurebits[1] << endl;
    cout << "CPU featurebits[2] = " << uid.cpu_featurebits[2] << endl;
    cout << "Product  = " << uid.product << endl;
    cout << "Version  = " << uid.version << endl;
    cout << "Serial   = " << uid.serial << endl;
    cout << "Features = " << uid.features << endl;
    cout << "EXE Addr  = " << uid.executable_addr << endl;
    cout << "EXE Hash  = " << toHex(uid.executable_hash, HASH_ALGO::DIGESTSIZE) << endl;
    cout << "Salt 1    = " << toHex(uid.salt, 32) << endl;
    cout << "Random    = " << toHex(uid.random, 32) << endl;
    cout << "UID Hash1 = " << toHex(uid.hash1, HASH_ALGO::DIGESTSIZE) << endl;
    cout << "UID Hash2 = " << toHex(uid.hash2, HASH_ALGO::DIGESTSIZE) << endl;
}

int License::checkLicense1(byte* license, int size)
{
    // assert(size == LI_SIZE);
    int buffer_size = HASH_ALGO::DIGESTSIZE + size + 32;
    byte* buffer = new byte[buffer_size];
    memcpy(buffer, &lInfo.uid.hash1, HASH_ALGO::DIGESTSIZE);
    memcpy(buffer + HASH_ALGO::DIGESTSIZE, license, size);
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
    memcpy(lInfo.license, license, size);
    delete[] buffer;
    return flag;
}

int License::checkLicense1(string license)
{
    int len;
    byte* buffer;
    fromHex(license, buffer, len);
    int res = checkLicense1(buffer, len);
    delete[] buffer;
    return res;
}

string License::generateLicense1()
{
    byte license[LI_SIZE];
    memset(license, 0, LI_SIZE);
    AutoSeededRandomPool rng;

    bool done = false;
    unsigned int t=20000000;  // HASH_ALGO::DIGESTSIZE / ZERO_BYTES;
    unsigned int i;
    for(i=0; i<t; i++)
    {
        rng.GenerateBlock(license, LI_SIZE);
        //memcpy(license, &i, 4);
        if(checkLicense1(license, LI_SIZE)==ZERO_BYTES)
        {
            done = true;
            break;
        }
    }
    cout << "I = " << i << endl;

    if(done) return toHex(license, LI_SIZE);
    else return "FAILED!";
}

int License::checkLicense2()
{
    //encrypt lInfo with the public key and send it to the server.
    //server opens it with the private key
    //server checks the licence, exe hash, ...
    //
    string a,b;
    RsaGenerateStringKeys(a,b);
    cout<<"PRIVATE: "<<a<<endl<<"PUBLIC: "<<b<<endl;
    return 0;
}

