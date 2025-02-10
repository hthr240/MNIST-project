#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
#include "iostream"
#include "cmath"

typedef Matrix (*ActivationFunction)(const Matrix &);
namespace activation
{
    Matrix relu(const Matrix &m);
    Matrix softmax(const Matrix &m);
}

#endif // ACTIVATION_H