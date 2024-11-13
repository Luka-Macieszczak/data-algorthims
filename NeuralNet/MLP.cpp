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

std::vector<std::vector<Value*>> MLP::out(std::vector<Value*> x) {
    std::vector<std::vector<Value*>> results{x};
    for(auto& layer : layers) {
        results.push_back(layer->out(results[results.size() - 1]));
    }
    return results;
}