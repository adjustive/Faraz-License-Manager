#ifndef HARDWAREUID_H
#define HARDWAREUID_H

#include <iostream>
#include <unistd.h>
#include "cpuid.h"

using namespace std;

struct HardwareUID
{
    long hostid;
    char cpu_vendor[13];
    //char alignment[3];
    unsigned int cpu_signature;
    unsigned int cpu_featurebits[3];

    void collect()
    {
        CPUID cpuID;
        //alignment[0] = alignment[1] = alignment[2] = 0;

        // hostid (returns a value based on the IP address)
        hostid = gethostid();

        cpuID.load(0); // Get CPU vendor
        memcpy(&cpu_vendor[0], &cpuID.EBX(), 4);
        memcpy(&cpu_vendor[4], &cpuID.EDX(), 4);
        memcpy(&cpu_vendor[8], &cpuID.ECX(), 4);
        cpu_vendor[12] = 0;

        cpuID.load(1); // Processor Info and Feature Bits
        cpu_signature = cpuID.EAX();
        cpu_featurebits[0] = cpuID.EDX();
        cpu_featurebits[1] = cpuID.ECX();
        cpu_featurebits[2] = cpuID.EBX() & 0x00FFFFFF; // ignore first 2 bytes

    }

    void print()
    {
        cout << "Host id            = " << hostid             << endl;
        cout << "CPU vendor         = " << cpu_vendor         << endl;
        cout << "CPU signature      = " << cpu_signature      << endl;
        cout << "CPU featurebits[0] = " << cpu_featurebits[0] << endl;
        cout << "CPU featurebits[1] = " << cpu_featurebits[1] << endl;
        cout << "CPU featurebits[2] = " << cpu_featurebits[2] << endl;
    }
};

#endif // HARDWAREUID_H
