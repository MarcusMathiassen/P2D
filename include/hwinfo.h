#ifndef HWINFO_H
#define HWINFO_H

#include <string>
#include <sys/types.h>
#include <sys/sysctl.h>

uint64_t 		get_cpu_freq();
uint64_t 		get_cpu_cores();
uint64_t 		get_cpu_threads();
std::string 	get_cpu_brand();


#endif