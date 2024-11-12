#include "Neuron.h"
#include <cmath>

Neuron::Neuron(unsigned int input_params) {
    // Generate random floats between -1 and 1
    activation_bias = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/2)) - 1;

    // Parallelism speed up here
    for(int i = 0; i < input_params; ++i) {
        weights[i] = static_cast <double> (rand()) / (static_cast <double> (RAND_MAX/2)) - 1;
    }
}

// use tanh(x) as squash function
double Neuron::squash(double out) {
    return (std::exp(out) - std::exp(-out)) / (std::exp(out) + std::exp(-out));
}

double Neuron::out(std::vector<double> x) {
    // Take dot product, add activaion, and squash
    // Also potential speed up
    if(x.size() != weights.size()) {
        // TODO
        return 0; 
    }

    double out = activation_bias;
    for(int i = 0; i < weights.size(); ++i) {
        out += weights[i] * x[i];
    }

    return squash(out);
}