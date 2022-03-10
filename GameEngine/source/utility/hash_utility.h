#pragma once
#include <stdint.h>

inline uint64_t SimpleHashULong(const unsigned long _a, const unsigned long _b) { return _a ^ _b; }
inline int64_t	SimpleHashLong(const long _a, const long _b) { return _a ^ _b; }