#ifndef VALUE_H
#define VALUE_H
#include <stdio.h>
#include <unordered_set>
#include <vector>

enum Operation {ADD, MULTIPLY, EXP, START};
class Value {
    // I don't really like this
    Operation _op;
    Value* _out;
    double _other;
    std::unordered_set<Value*> children;

    double data;
    double grad;

    void build_topo(std::vector<Value*>& topo_sorting, std::unordered_set<Value*>& visited, Value* cur);

    public:
    Value(double d, std::unordered_set<Value*>c = std::unordered_set<Value*>{});
    ~Value();
    double get_data();
    double get_grad();
    friend Value* operator+(Value& c1, Value& c2);
    friend Value* operator*(Value& c1, Value& c2);

    void _backward();
    void backward();
};
#endif