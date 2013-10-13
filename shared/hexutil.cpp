#include "hexutil.h"

HexUtil::HexUtil()
{
}

string HexUtil::toHex(byte *input, int len)
{
    HexEncoder encoder;
    string output;

    encoder.Attach(new StringSink(output)); // FIXME
    //StringSink ss(output);
    //encoder.Attach(&ss);
    //StringSink *ss = new StringSink(output);
    //encoder.Attach(ss);

    encoder.Put(input, len);
    encoder.MessageEnd();
    //delete ss;
    return output;
}

vector<byte> HexUtil::fromHex(string input)
{
    vector<byte>output;

    HexDecoder decoder;
    decoder.Put((byte*) input.c_str(), input.length());
    decoder.MessageEnd();

    word64 size = decoder.MaxRetrievable();
    if(size)
    {
        output.resize(size);
        decoder.Get(output.data(), size);
    }
    return output;
}
