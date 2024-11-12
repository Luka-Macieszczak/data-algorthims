#ifndef VALUE_H
#define VALUE_H
enum Operation {ADD, MULTIPLY, EXP};
class Value {
    // I don't really like this
    Operation _op;
    double _out;
    double _other;

    double data;
    double grad;

    public:
    Value();
    double backward();
    friend Value operator+(Value& c1, Value& c2);
};
#endif