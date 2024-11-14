#include "MLP.h"
#include "Neuron.h"
#include "Value.h"
#include <stdio.h>

void test_value() {
    Value* v1 = new Value(0.5), *v2 = new Value(0.3);
    Value* v3 = (*v1) * (*v2);
    Value* v4 = new Value(0.1);
    Value* v5 = *v4 + *v3;
    Value* out = v5->tanh();
    
    out->backward();

    printf("data: %f out grad: %f v1 grad: %f, v2 grad: %f, v3 grad: %f, v4 grad: %f, v5 grad: %f",
    out->get_data(), out->get_grad(), v1->get_grad(), v2->get_grad(), v3->get_grad(), v4->get_grad(), v5->get_grad());
}

void test_neuron() {
    std::vector<Value*> x;
    for(int i = 0; i < 6; ++i) {
        x.push_back(new Value(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/2)) - 1));
    }
    Neuron test(6);

    Value* out2 = test.out(x);

    out2->backward();

    printf("out2: %f\n", out2->get_data());

    for(int i = 0; i < x.size(); ++i) {
        printf("value: %f   grad: %f\n", x[i]->get_data(), x[i]->get_grad());
    }
}

void test_layer() {
    std::vector<Value*> x;
    for(int i = 0; i < 2; ++i) {
        x.push_back(new Value(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/2)) - 1));
    }
    Layer test(2, 1);
    auto res = test.out(x);

    printf("res: %f\n", res[res.size() - 1]->get_data());
    res[res.size() - 1]->backward();

    for(int i = 0; i < x.size(); ++i) {
        printf("value: %f   grad: %f\n", x[i]->get_data(), x[i]->get_grad());
    }
}

void test_mlp() {
    std::vector<Value*> x;
    for(int i = 0; i < 6; ++i) {
        x.push_back(new Value(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/2)) - 1));
    }

    MLP test{std::vector<unsigned int>{6, 16, 16, 1}};
    auto res = test.out(x);
    res[0]->backward();
    printf("result val: %f", res[0]->get_data());

    for(auto& v : x) {
        printf("val: %f     grad: %f\n", v->get_data(), v->get_grad());
    }
}

int main() {
    test_mlp();
    return 0;
}