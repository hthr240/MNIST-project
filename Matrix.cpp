#include "Matrix.h"

// allocate memory for the matrix
Matrix::Matrix(int rows, int columns) : dims({rows, columns})
{
    if (rows < 1 || columns < 1)
    {
        throw std::length_error(SIZE_ERR);
    }
    data = new float[rows * columns];
    for (int i = 0; i < (dims.rows * dims.cols); i++)
    {
        data[i] = 0;
    }
}

Matrix::Matrix() : dims({1, 1})
{
    data = new float[1];
    data[0] = 0;
}

Matrix::Matrix(const Matrix &m) : dims({m.dims.rows, m.dims.cols})
{
    data = new float[dims.rows * dims.cols];
    for (int i = 0; i < (dims.rows * dims.cols); i++)
    {
        data[i] = m.data[i];
    }
}

Matrix::~Matrix()
{
    delete[] data;
}

// get rows
int Matrix::get_rows() const
{
    return dims.rows;
}

// get cols
int Matrix::get_cols() const
{
    return dims.cols;
}

// transpose
Matrix &Matrix::transpose()
{
    float *arr = new float[dims.rows * dims.cols];
    int tmp = dims.rows;
    dims.rows = dims.cols;
    dims.cols = tmp;
    for (int i = 0; i < dims.rows; i++)
    {
        for (int j = 0; j < dims.cols; j++)
        {
            arr[i * dims.cols + j] = data[j * dims.rows + i];
        }
    }
    delete[] data;
    data = arr;
    return *this;
}

Matrix &Matrix::vectorize()
{
    dims.rows = (dims.rows * dims.cols);
    dims.cols = 1;
    return *this;
}

void Matrix::plain_print() const
{
    int k = 0;
    for (int i = 0; i < dims.rows; i++)
    {
        for (int j = 0; j < dims.cols; j++, k++)
        {
            std::cout << data[k] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::dot(const Matrix &m) const
{
    if (this->dims.rows != m.dims.rows || this->dims.cols != m.dims.cols)
    {
        throw std::invalid_argument(DIMS_NOT_MATCH);
    }

    Matrix result(m.dims.rows, m.dims.cols);

    for (int i = 0; i < (m.dims.rows * m.dims.cols); ++i)
    {
        result.data[i] = data[i] * m.data[i];
    }

    return result;
}

float Matrix::norm() const
{
    float x = 0;
    for (int i = 0; i < (dims.rows * dims.cols); i++)
    {
        x += powf(data[i], 2);
    }
    return sqrtf(x);
}

Matrix Matrix::rref() const
{
    Matrix m(*this);
    int r = 0;
    for (int j = 0; j < dims.cols; j++)
    {
        bool zero_col = true;
        for (int i = r; i < dims.rows; i++)
        {
            if (m(i, j) != 0)
            {
                m.op_swap_rows(i, r);
                zero_col = false;
                break;
            }
        }
        if (zero_col)
        {
            continue;
        }
        m.op_mult_row_by_a(r, 1 / (m(r, j)));
        for (int i = 0; i < dims.rows; i++)
        {
            if (m(i, j) != 0 && i != r)
            {
                m.op_add_mult_row(-m(i, j), r, i);
            }
        }
        r++;
    }
    return m;
}

int Matrix::argmax() const
{
    float max = data[0];
    int ind = 0;
    for (int i = 1; i < (dims.rows * dims.cols); i++)
    {
        if (data[i] > max)
        {
            max = data[i];
            ind = i;
        }
    }
    return ind;
}

float Matrix::sum() const
{
    float x = 0;
    for (int i = 0; i < (dims.rows * dims.cols); i++)
    {
        x += data[i];
    }
    return x;
}

Matrix &Matrix::operator+=(const Matrix &m)
{
    if (dims.rows == m.dims.rows && dims.cols == m.dims.cols)
    {
        for (int i = 0; i < (dims.rows * dims.cols); i++)
        {
            data[i] += m.data[i];
        }
        return *this;
        ;
    }
    else
    {
        throw std::length_error(DIMS_NOT_MATCH);
    }
}

Matrix Matrix::operator+(const Matrix &m) const
{
    if (this->dims.rows == m.dims.rows && this->dims.cols == m.dims.cols)
    {
        Matrix result(m.dims.rows, m.dims.cols);
        for (int i = 0; i < (m.dims.rows * m.dims.cols); i++)
        {
            result.data[i] = data[i] + m.data[i];
        }
        return result;
    }
    else
    {
        throw std::length_error(DIMS_NOT_MATCH);
    }
}

Matrix &Matrix::operator=(const Matrix &m)
{
    if (this != &m)
    {
        float *tmp = data;
        data = new float[(m.dims.rows * m.dims.cols)];
        for (int i = 0; i < (m.dims.rows * m.dims.cols); i++)
        {
            data[i] = m.data[i];
        }
        delete[] tmp;
        dims.rows = m.dims.rows;
        dims.cols = m.dims.cols;
    }
    return *this;
}

Matrix Matrix::operator*(const Matrix &m) const
{
    if (dims.cols == m.dims.rows)
    {
        Matrix result(dims.rows, m.dims.cols);
        for (int i = 0; i < dims.rows; i++)
        {
            for (int j = 0; j < m.dims.cols; j++)
            {
                float x = 0;
                for (int k = 0; k < dims.cols; k++)
                {
                    x += ((*this)(i, k) * m(k, j));
                }
                result.data[i * result.dims.cols + j] = x;
            }
        }
        return result;
    }
    else
    {
        throw std::length_error(DIMS_NOT_MATCH);
    }
}

Matrix operator*(float scalar, const Matrix &m)
{
    Matrix result(m.dims.rows, m.dims.cols);

    for (int i = 0; i < (m.dims.rows * m.dims.cols); i++)
    {
        result.data[i] = m.data[i] * scalar;
    }
    return result;
}

Matrix Matrix::operator*(float scalar) const
{
    Matrix new_mat(this->dims.rows, this->dims.cols);
    for (int i = 0; i < (dims.rows * dims.cols); i++)
    {
        new_mat.data[i] = data[i] * scalar;
    }
    return new_mat;
}

float Matrix::operator()(int i, int j) const
{
    if (0 <= i && i < dims.rows && 0 <= j && j < dims.cols)
    {
        return data[i * dims.cols + j];
    }
    else
    {
        throw std::out_of_range(RANGE_ERR);
    }
}

float &Matrix::operator()(int i, int j)
{
    if (0 <= i && i < dims.rows && 0 <= j && j < dims.cols)
    {
        return data[i * dims.cols + j];
    }
    else
    {
        throw std::out_of_range(RANGE_ERR);
    }
}

float Matrix::operator[](int k) const
{
    if (0 <= k && k < (dims.rows * dims.cols))
    {
        return data[k];
    }
    else
    {
        throw std::out_of_range(RANGE_ERR);
    }
}

float &Matrix::operator[](int k)
{
    if (0 <= k && k < (dims.rows * dims.cols))
    {
        return data[k];
    }
    else
    {
        throw std::out_of_range(RANGE_ERR);
    }
}

std::ostream &operator<<(std::ostream &os, const Matrix &m)
{
    for (int i = 0; i < m.dims.rows; ++i)
    {
        for (int j = 0; j < m.dims.cols; ++j)
        {
            if (m(i, j) > VALUE)
            {
                os << "**";
            }
            else
            {
                os << "  ";
            }
        }
        os << std::endl;
    }
    return os;
}

std::istream &operator>>(std::istream &is, Matrix &m)
{
    long unsigned int loc = is.tellg();
    is.seekg(0, std::istream::end);
    long unsigned int length = is.tellg();
    is.seekg(loc);
    if (length < (m.dims.rows * m.dims.cols) * sizeof(float))
    {
        throw std::runtime_error("");
    }
    if (!is.read((char *)m.data, (m.dims.rows * m.dims.cols) * sizeof(float)))
    {
        throw std::runtime_error("");
    }
    return is;
}

Matrix &Matrix::op_add_mult_row(float a, int src, int dest)
{
    for (int j = 0; j < dims.cols; j++)
    {
        data[dest * dims.cols + j] += (a * data[src * dims.cols + j]);
    }
    return *this;
}

Matrix &Matrix::op_mult_row_by_a(int r, float a)
{
    for (int j = 0; j < dims.cols; j++)
    {
        data[r * dims.cols + j] *= a;
    }
    return *this;
}

Matrix &Matrix::op_swap_rows(int r1, int r2)
{
    for (int j = 0; j < dims.cols; j++)
    {
        float tmp = data[r1 * dims.cols + j];
        data[r1 * dims.cols + j] = data[r2 * dims.cols + j];
        data[r2 * dims.cols + j] = tmp;
    }
    return *this;
}
