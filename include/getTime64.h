#ifndef GETTIME64_H
#define GETTIME64_H

#ifdef _WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#include <ctime>
#endif

/* Returns the amount of milliseconds elapsed since the UNIX epoch. Works on
 * both
 * windows and linux. */

/* Remove if already defined */
typedef long long int64;
typedef unsigned long long uint64;

uint64 GetTimeMs64();

#endif
