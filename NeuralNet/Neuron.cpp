#include "Neuron.h"
#include <cmath>

Neuron::Neuron(unsigned int input_params) {
    // Generate random floats between -1 and 1
    activation_bias = new Value(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/2)) - 1);

    // Possible parallelism speed up here
    for(int _ = 0; _ < input_params; ++_) {
        weights.push_back(new Value(static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/2)) - 1));
    }
}

Neuron::~Neuron() {
    delete (activation_bias);
    for(auto w : weights) {
        delete (w);
    }
}

// Compute sum as a complete binary tree with about 2n nodes
// Squish adjacent elements into single values until reaching 1
// Height is logarithmic opposed to linear
Value* Neuron::sum(std::vector<Value*>& sum_elements) {
    if(sum_elements.size() == 1) {
        return sum_elements[0];
    }

    std::vector<Value*> intermediate_values;

    for(int i = 0; i < sum_elements.size(); i += 2) {
        if(i + 1 >= sum_elements.size()){
            intermediate_values.push_back(sum_elements[i]);
            break;
        }

        intermediate_values.push_back(*sum_elements[i] + *sum_elements[i + 1]);
    }

    return sum(intermediate_values);
}

Value* Neuron::out(std::vector<Value*> x) {
    // Take dot product, add activaion, and squash
    // Also potential speed up
    if(x.size() != weights.size()) {
        // TODO
        return 0; 
    }

    std::vector<Value*> sum_elements;

    for(int i = 0; i < weights.size(); ++i) {
        sum_elements.push_back((*weights[i]) * (*x[i]));
    }

    Value* out = sum(sum_elements);

    return out->tanh();
}