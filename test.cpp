#include <stdio.h>
#include "BloomFilter/BloomFilter.h"
#include <cstring>
#include <vector>
#include <string>


void test_bloom() {
    printf("Hello World\n");

    std::vector<std::string> filter{
        "Hello\0",
        "World\0",
        "Ryan\0",
        "Farokhi\0"
    };

    BloomFilter bf{filter, 5, 50};
    bf.print_bucket_arr();
    printf("is %s in bf?: %d\n", filter[0].c_str(), bf.query(filter[0]));
    std::string q2 = "tlpatek";
    printf("is %s in bf?: %d\n", q2.c_str(), bf.query(q2));
}

int main() {
    test_bloom();
    return 0;
}
