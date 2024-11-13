#ifndef NEURON_H
#define NEURON_H
#include <vector>
#include <random>
#include <cmath>
#include "Value.h"

class Neuron {
    Value* activation_bias;
    std::vector<Value*> weights;

    Value* sum(std::vector<Value*>& sum_elements);

    public:
    Neuron(unsigned int input_params);
    ~Neuron();
    Value* out(std::vector<Value*> x);
};

#endif