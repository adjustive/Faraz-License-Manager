#ifndef CPUID_H
#define CPUID_H

#include <stdint.h>

class CPUID
{
    uint32_t regs[4];

public:
    void load(unsigned i)
    {
        asm volatile
        (
        "cpuid" : "=a" (regs[0]),
        "=b" (regs[1]),
        "=c" (regs[2]),
        "=d" (regs[3]) : "a" (i), "c" (0)
        );
        // ECX is set to zero for CPUID function 4
    }

    const uint32_t &EAX() const {return regs[0];}
    const uint32_t &EBX() const {return regs[1];}
    const uint32_t &ECX() const {return regs[2];}
    const uint32_t &EDX() const {return regs[3];}
};

#endif // CPUID_H
