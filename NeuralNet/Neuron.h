#ifndef NEURON_H
#define NEURON_H
#include <vector>
#include <random>
#include <cmath>

class Neuron {
    double activation_bias;
    std::vector<double> weights;

    double squash(double out);
    public:
    Neuron(unsigned int input_params);
    ~Neuron();
    double out(std::vector<double> x);
};

#endif