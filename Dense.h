// Dense.h
#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense
{
private:
    Matrix _weights;
    Matrix _bias;
    ActivationFunction _func;

public:
    Dense(const Matrix &weights, const Matrix &bias, ActivationFunction func); // constructor

    Matrix get_weights() const;                // get weights
    Matrix get_bias() const;                   // get_bias
    ActivationFunction get_activation() const; // get activation func
    Matrix operator()(Matrix m) const;         // apply operator
};

#endif // DENSE_H