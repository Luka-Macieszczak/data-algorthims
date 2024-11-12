#include "Value.h"
#include <stdio.h>

int main() {
    Value* v1 = new Value(2), *v2 = new Value(3);
    Value* out = (*v1) * (*v2);
    
    out->backward();

    printf("data: %f out grad: %f v1 grad: %f, v2 grad: %f",
    out->get_data(), out->get_grad(), v1->get_grad(), v2->get_grad());
    return 0;
}