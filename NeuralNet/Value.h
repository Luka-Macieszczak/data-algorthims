#ifndef VALUE_H
#define VALUE_H
#include <stdio.h>
#include <unordered_set>
#include <vector>

class Value;

enum Operation {ADD, MULTIPLY, EXP, START, TANH};

typedef struct Evaluation {
    Value* out;
    Operation op;
    double other;
} Evaluation;

class Value {
    // I don't really like this
    std::vector<Evaluation> evals;
    std::unordered_set<Value*> children;
    int refs;

    double data;
    double grad;

    void build_topo(std::vector<Value*>& topo_sorting, std::unordered_set<Value*>& visited, Value* cur);
    double _tanh(double x);

    public:
    Value(double d, std::unordered_set<Value*>c = std::unordered_set<Value*>{}, int r=0);
    ~Value();
    double get_data();
    double get_grad();
    friend Value* operator+(Value& c1, Value& c2);
    friend Value* operator*(Value& c1, Value& c2);
    Value* tanh();

    void _backward();
    void backward();
};
#endif