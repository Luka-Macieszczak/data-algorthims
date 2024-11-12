#include "BloomFilter.h"
#include <cstring>

void set_bit(unsigned char* byte, int bit) {
    *byte |= 1 << (7 - bit);
}

int get_bit(unsigned char byte, int bit) {
    return (byte >> (7 - bit)) & 1;
}

BloomFilter::~BloomFilter() {
    delete(bucket_arr);
}

BloomFilter::BloomFilter(std::vector<std::string>& filter, int hash_count, unsigned int bucket_count) {
    // Round the bucket count up to a multiple of 8
    bucket_count += 8 - (bucket_count % 8);
    bucket_arr_length = bucket_count / 8;
    bucket_arr = (unsigned char*) malloc((size_t) bucket_arr_length);
    
    // Create and store random hash functions
    for(int i = 0; i < hash_count; ++i) {
        hash_functions.push_back(HashFunction{bucket_count});
    }

    // Filter in this context is the set we want to filter
    for(auto& filter_string : filter) {
        for(auto& hash_func : hash_functions) {
            unsigned int b_idx = hash_func.at(filter_string.c_str(), filter_string.size());
            set_bucket(b_idx);
        }
    }
}

void BloomFilter::print_bucket_arr() {
    std::cout<<"[ ";
    int byte = 0, bit = 7;
    for(int i = 0; i < bucket_arr_length * 8; ++i) {
        if(bit == -1) {
            ++byte;
            bit = 7;
        }
        printf("%d ", get_bit(bucket_arr[byte], bit));
        --bit;
    }
    std::cout<<" ]\n";
}

bool BloomFilter::query(std::string& q) {
    for(auto& hash_func : hash_functions) {
        unsigned int b_idx = hash_func.at(q.c_str(), q.size());
        if(!check_bucket(b_idx)) {
            return false;
        }
    }
    return true;
}

bool BloomFilter::query(const char* q) {
    for(auto& hash_func : hash_functions) {
        unsigned int b_idx = hash_func.at(q, strlen(q));
        if(!check_bucket(b_idx)) {
            return false;
        }
    }
    return true;
}

unsigned char BloomFilter::check_bucket(int idx) {
    return get_bit(bucket_arr[idx / 8], idx % 8);
}

void BloomFilter::set_bucket(int idx) {
    set_bit(&bucket_arr[idx / 8], idx % 8);
}