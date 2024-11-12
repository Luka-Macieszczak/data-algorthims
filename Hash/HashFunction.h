#ifndef HASH_FUNCTION_H
#define HASH_FUNCTION_H
#include <chrono>

enum HashScheme{JS, DJB, AP};

class HashFunction {
    static unsigned int idx;
    unsigned int seed;
    unsigned int scheme;
    unsigned int range;
    public:
    HashFunction(unsigned int r);
    unsigned int at(const char* bytes, unsigned int size);
};
#endif