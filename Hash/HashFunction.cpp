#include "HashFunction.h"

unsigned int JSHash(const char* str, unsigned int length, int seed) {
   unsigned int hash = seed;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((hash << 5) + (*str) + (hash >> 2));
   }

   return hash;
}

unsigned int DJBHash(const char* str, unsigned int length, int seed) {
   unsigned int hash = seed % 5381;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash = ((hash << 5) + hash) + (*str);
   }

   return hash;
}

unsigned int APHash(const char* str, unsigned int length, int seed) {
   unsigned int hash = seed;
   unsigned int i    = 0;

   for (i = 0; i < length; ++str, ++i)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash;
}

unsigned int HashFunction::idx = 0;

HashFunction::HashFunction(unsigned int r) {
    ++HashFunction::idx;
    auto time = std::chrono::high_resolution_clock::now();
    seed = std::chrono::time_point_cast<std::chrono::nanoseconds>(time).time_since_epoch().count();
    scheme = (seed + idx) % 3;
    range = r;
}

unsigned int HashFunction::at(const char* bytes, unsigned int size) {
    switch (scheme) {
        case JS:
            return JSHash(bytes, size, seed) % range;
            break;
        case DJB:
            return DJBHash(bytes, size, seed) % range;
        case AP:
            return APHash(bytes, size, seed) % range;
        default:
            break;
    }

    return 0;
}