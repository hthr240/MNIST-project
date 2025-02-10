
#include "Dense.h"
#define DIMS_NOT_MATCH "Matrices dimensions do not match for action."

Dense::Dense(const Matrix &weights, const Matrix &bias, ActivationFunction func) : _weights(weights), _bias(bias), _func(func)
{
    if (bias.get_cols() != 1 || weights.get_rows() != bias.get_rows())
    {
        throw std::length_error(DIMS_NOT_MATCH); // handle
    }
}

// Getter for weights
Matrix Dense::get_weights() const
{
    return _weights;
}

// Getter for bias
Matrix Dense::get_bias() const
{
    return _bias;
}

// Getter for activation function
ActivationFunction Dense::get_activation() const
{
    return _func;
}

// Operator() to apply the layer on the input matrix
Matrix Dense::operator()(Matrix m) const
{
    return _func(_weights * m + _bias);
}
