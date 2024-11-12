#ifndef H_BLOOM_FILTER
#define H_BLOOM_FILTER
#include <vector>
#include "../Hash/HashFunction.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
class BloomFilter {
    unsigned char* bucket_arr;
    int bucket_arr_length;
    std::vector<HashFunction> hash_functions;

    public:
        BloomFilter(std::vector<std::string>& filter, int hash_count, unsigned int bucket_count);
        BloomFilter(unsigned char** filter, int filter_size, float false_positive_rate);
        ~BloomFilter();
        void print_bucket_arr();
        bool query(std::string& q);
        bool query(const char* q);
    private:
        unsigned char check_bucket(int idx);
        void set_bucket(int idx);
};
#endif