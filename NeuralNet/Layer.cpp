#include "Layer.h"

Layer::Layer(unsigned int input_params, unsigned int n_out) {
    for(int _ = 0; _ < n_out; _++) {
        neurons.push_back(new Neuron{input_params});
    }

    output_params = n_out;
}

Layer::~Layer() {
    for(auto neuron : neurons) {
        delete(neuron);
    }
}

std::vector<Value*> Layer::out(std::vector<Value*> x) {
    std::vector<Value*> ret;
    for(auto& neuron : neurons) {
        ret.push_back(neuron->out(x));
    }

    return ret;
}