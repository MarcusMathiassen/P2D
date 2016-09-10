#include "hwinfo.h"

uint64_t get_cpu_freq()
{
    uint64_t num = 0;
    size_t size = sizeof(num);

    if (sysctlbyname("hw.cpufrequency", &num, &size, NULL, 0) < 0)
    {
        perror("sysctl");
    }
    return num;
}

uint64_t get_cpu_cores()
{
    uint64_t num = 0;
    size_t size = sizeof(num);

    if (sysctlbyname("hw.physicalcpu_max", &num, &size, NULL, 0) < 0)
    {
        perror("sysctl");
    }
    return num;
}

uint64_t get_cpu_threads()
{
    uint64_t num = 0;
    size_t size = sizeof(num);

    if (sysctlbyname("hw.logicalcpu_max", &num, &size, NULL, 0) < 0)
    {
        perror("sysctl");
    }
    return num;
}

std::string get_cpu_brand()
{
    char buffer[128];
    size_t bufferlen = 128;

    sysctlbyname("machdep.cpu.brand_string",&buffer,&bufferlen,NULL,0);

    return buffer;
}