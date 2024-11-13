#ifndef MLP_H
#define MLP_H
#include "Neuron.h"
#include "Layer.h"
#include "Value.h"
#include <stdio.h>
#include <vector>
class MLP {
    std::vector<Layer*> layers;
    public:
    // schema defines how many inputs/outputs per layer
    // Layer i would have schema[i-1] many inputs, and schema[i] many outputs
    // Last element in schema is size of final Value* vector returned by MLP
    MLP(std::vector<unsigned int> schema);
    ~MLP();

    // x should have length schema[0]
    // returns vector with length schema[schem.size() - 1]
    std::vector<std::vector<Value*>> out(std::vector<Value*> x);
};

#endif