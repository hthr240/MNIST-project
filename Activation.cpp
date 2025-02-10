#include "Activation.h"

Matrix activation::relu(const Matrix &m)
{
    Matrix result(m.get_rows(), m.get_cols());
    for (int i = 0; i < m.get_rows(); i++)
    {
        for (int j = 0; j < m.get_cols(); j++)
        {
            if (m(i, j) > 0)
            {
                result(i, j) = m(i, j);
            }
        }
    }
    return result;
}

Matrix activation::softmax(const Matrix &m)
{
    float h = 0;
    for (int k = 0; k < m.get_cols() * m.get_rows(); k++)
    {
        h += std::exp(m[k]);
    }
    Matrix result(m);
    for (int k = 0; k < m.get_cols() * m.get_rows(); k++)
    {
        result[k] = std::exp(m[k]);
    }
    return (1 / h) * result;
}
