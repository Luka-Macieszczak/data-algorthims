#include "MLP.h"
MLP::MLP(std::vector<unsigned int> schema) {
    for(int i = 1; i < schema.size(); ++i) {
        layers.push_back(new Layer{schema[i - 1], schema[i]});
    }
}

MLP::~MLP(){
    for(auto layer : layers) {
        delete (layer);
    }
}

std::vector<Value*> MLP::out(std::vector<Value*> x) {
    for(auto& layer : layers) {
        x = layer->out(x);
    }
    return x;
}