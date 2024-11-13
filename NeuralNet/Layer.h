#ifndef LAYER_H
#define LAYER_H
#include "Neuron.h"
#include "Value.h"
#include <stdio.h>
#include <vector>

class Layer {
    std::vector<Neuron*> neurons;
    unsigned int output_params;

    public:
    Layer(unsigned int input_params, unsigned int n_out);
    ~Layer();

    std::vector<Value*> out(std::vector<Value*> x);
};

#endif