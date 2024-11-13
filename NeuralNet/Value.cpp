#include "Value.h"

Value::Value(double d, std::unordered_set<Value*>c, int r) {
    grad = 0;
    data = d;
    refs = r;
    children = c;
}

Value::~Value() {    
    // Keep track of how many children nodes still reference _out
    for(auto eval : evals) {
        --eval.out->refs;
        if(eval.out->refs <= 0)
            delete (eval.out);
    }
}

double Value::get_data() {
    return data;
}

double Value::get_grad() {
    return grad;
}

Value* operator+(Value& v1, Value& v2) {
    Value* out = new Value(0.0, std::unordered_set<Value*> {&v1, &v2}, 2);

    Evaluation eval1{out, ADD, v2.data};
    Evaluation eval2{out, ADD, v1.data};

    v1.evals.push_back(eval1);
    v2.evals.push_back(eval2);

    out->data = v1.data + v2.data;

    return out;
}

Value* operator*(Value& v1, Value& v2) {
    Value* out = new Value(0.0, std::unordered_set<Value*> {&v1, &v2}, 2);
    Evaluation eval1{out, MULTIPLY, v2.data};
    Evaluation eval2{out, MULTIPLY, v1.data};

    v1.evals.push_back(eval1);
    v2.evals.push_back(eval2);

    out->data = v1.data * v2.data;

    return out;
}

Value* Value::tanh() {
    Value* out = new Value(0.0, std::unordered_set<Value*> {this}, 1);

    Evaluation eval{out, TANH, 0};

    evals.push_back(eval);

    out->data = _tanh(data);

    return out;
}

double Value::_tanh(double x) {
    return (std::exp(x) - std::exp(-x)) / (std::exp(x) + std::exp(-x));
}

void Value::_backward() {
    for(auto& eval : evals) {
        switch (eval.op) {
        case ADD:
            grad += eval.out->grad;
            break;
        case MULTIPLY:
            grad += eval.other * eval.out->grad;
            break;
        case TANH:
            grad += (1 - pow(_tanh(data), 2)) * eval.out->grad;
            break;
        default:
            grad = 1;
            break;
        }
    }

    if(evals.empty()) grad = 1;
}

void Value::build_topo(std::vector<Value*>& topo_sorting, std::unordered_set<Value*>& visited, Value* cur) {
    if(visited.count(cur)) return;

    visited.insert(cur);

    for(auto& child : cur->children) {
        build_topo(topo_sorting, visited, child);
    }

    topo_sorting.push_back(cur);
}

void Value::backward() {
    std::unordered_set<Value*> visited;
    std::vector<Value*> topo_sorting;
    
    build_topo(topo_sorting, visited, this);

    for(int i = topo_sorting.size() - 1; i >= 0; --i) {
        topo_sorting[i]->_backward();
    }
}