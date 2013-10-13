#ifndef HARDWAREUID_H
#define HARDWAREUID_H

struct HardwareUID
{
    long hostid;
    char cpu_vendor[13];
    //char alignment[3];
    unsigned int cpu_signature;
    unsigned int cpu_featurebits[3];
};

#endif // HARDWAREUID_H
