#include "MlpNetwork.h"
#define SIZE_ERR "Matrices lengths are not compatibale."

// Constructor
MlpNetwork::MlpNetwork(const Matrix *weights, const Matrix *biases) : d0(Dense(weights[0], biases[0], activation::relu)),
                                                                      d1(Dense(weights[1], biases[1], activation::relu)),
                                                                      d2(Dense(weights[2], biases[2], activation::relu)),
                                                                      d3(Dense(weights[3], biases[3], activation::softmax))
{
    if (d0.get_weights().get_rows() != d1.get_weights().get_cols() ||
        d1.get_weights().get_rows() != d2.get_weights().get_cols() ||
        d2.get_weights().get_rows() != d3.get_weights().get_cols())
    {
        throw std::length_error(SIZE_ERR);
    }
}

// Operator() to apply the network on the input matrix
digit MlpNetwork::operator()(const Matrix &image) const
{
    Matrix m(image);
    m.vectorize();
    Matrix r1 = d0(m);
    Matrix r2 = d1(r1);
    Matrix r3 = d2(r2);
    Matrix r4 = d3(r3);
    unsigned int k = r4.argmax();
    digit digit = {k, r4[(int)k]};
    return digit;
}
