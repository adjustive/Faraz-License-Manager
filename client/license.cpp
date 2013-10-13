#include "license.h"

License::License(unsigned int s, unsigned int f)
{
    setSerial(s);
    setFeatures(f);
    initUID = getUniqueID();
    lInfo.uid = initUID;
}

License::~License()
{

}

UniqueID License::getInitUID()
{
    return initUID;
}

void License::setFeatures(unsigned int f)
{
    features = f;
}

void License::setSerial(unsigned int s)
{
    serial = s;
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

UniqueID License::getUniqueID() const
{
    HASH_ALGO hash;
    UniqueID result;
    CPUID cpuID;

    //result.alignment[0] = result.alignment[1] = result.alignment[2] = 0;

    // hostid (returns a value based on the IP address)
    result.hostid = gethostid();

    cpuID.load(0); // Get CPU vendor
    memcpy(&result.cpu_vendor[0], &cpuID.EBX(), 4);
    memcpy(&result.cpu_vendor[4], &cpuID.EDX(), 4);
    memcpy(&result.cpu_vendor[8], &cpuID.ECX(), 4);
    result.cpu_vendor[12] = 0;

    cpuID.load(1); // Processor Info and Feature Bits
    result.cpu_signature = cpuID.EAX();
    result.cpu_featurebits[0] = cpuID.EDX();
    result.cpu_featurebits[1] = cpuID.ECX();
    result.cpu_featurebits[2] = cpuID.EBX() & 0x00FFFFFF; // ignore first 2 bytes

    // salt 1
    memcpy(result.salt, SALT_1, 32);

    // random
    AutoSeededRandomPool rng;
    rng.GenerateBlock(result.random, 32);
    //memset(result.random, 0, 32);

    // product & version & features
    result.product = PRODUCT_ID;
    result.version = PRODUCT_VER;
    result.serial = serial;
    result.features = features;

    // executable hash
    int exelen = readlink("/proc/self/exe", result.executable_addr, 512);
    memset(result.executable_addr + exelen, 0, 512 - exelen);
    FileSource(result.executable_addr, true,
               new HashFilter (hash,
               new ArraySink(result.executable_hash, HASH_ALGO::DIGESTSIZE))); //LEAK!

    // calc the hash
    hash.CalculateDigest(result.hash1, (byte*)&result, sizeof(result) - HASH_ALGO::DIGESTSIZE * 2 - 38); // FIXME 32
    hash.CalculateDigest(result.hash2, (byte*)&result, sizeof(result) - HASH_ALGO::DIGESTSIZE * 2);

    return result;
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
    memcpy(buffer, &initUID.hash1, HASH_ALGO::DIGESTSIZE);
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

int License::checkLicense2()
{
    //encrypt lInfo with the public key and send it to the server.
    //server opens it with the private key
    //server checks the licence, exe hash, ...
    //
    string pub = PUBLIC_KEY;

    return 0;
}

