#include "Value.h"

Value::Value(double d, std::unordered_set<Value*>c) {
    _out = nullptr;
    grad = 0;
    data = d;
    _op = START;
    children = c;
}

Value::~Value() {
   delete (_out);
}

double Value::get_data() {
    return data;
}

double Value::get_grad() {
    return grad;
}

Value* operator+(Value& v1, Value& v2) {
    Value* out = new Value(0.0, std::unordered_set<Value*> {&v1, &v2});
    v1._out = out, v2._out = out;
    v1._op = ADD, v2._op = ADD;

    out->data = v1.data + v2.data;

    return out;
}

Value* operator*(Value& v1, Value& v2) {
    Value* out = new Value(0.0, std::unordered_set<Value*> {&v1, &v2});

    v1._out = out, v2._out = out;
    v1._op = MULTIPLY, v2._op = MULTIPLY;
    v1._other = v2.data, v2._other = v1.data;

    out->data = v1.data * v2.data;

    return out;
}

void Value::_backward() {
    switch (_op) {
        case ADD:
            grad += _out->grad;
            break;
        case MULTIPLY:
            grad += _other * _out->grad;
            break;
        default:
            grad = 1;
            break;
    }
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