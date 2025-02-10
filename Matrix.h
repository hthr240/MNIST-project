// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H

#include "iostream"
#include "cmath"

#define DIMS_NOT_MATCH "Matrices dimensions do not match for action."
#define RANGE_ERR "Matrix indices out of range."
#define SIZE_ERR "Matrices lengths are not compatibale."

#define VALUE 0.1

// You don't have to use the struct. Can help you with MlpNetwork.h
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

class Matrix
{
private:
    matrix_dims dims;
    float *data;

    Matrix &op_add_mult_row(float a, int src, int dest);
    Matrix &op_mult_row_by_a(int r, float a);
    Matrix &op_swap_rows(int r1, int r2);

public:
    // default constructor
    Matrix();

    // constructor with dims ARGS -> rows , cols
    Matrix(int rows, int cols);

    // copy constructor
    Matrix(const Matrix &m);

    // deconstructor
    ~Matrix();

    // get rows
    int get_rows() const;

    // get cols
    int get_cols() const;

    // transopse : A -> At
    Matrix &transpose();

    // vectorize : matrix -> vector
    Matrix &vectorize();

    // prints matrix
    void plain_print() const;

    // dot matrix function
    Matrix dot(const Matrix &m) const;

    // norm function
    float norm() const;

    // rref
    Matrix rref() const;

    // get max element from matrix
    int argmax() const;

    // get sum of all elements in matrix
    float sum() const;

    // Operators

    Matrix &operator+=(const Matrix &m);                                // addition assignment
    Matrix operator+(const Matrix &m) const;                            // addition
    Matrix &operator=(const Matrix &m);                                 // assignement
    Matrix operator*(const Matrix &m) const;                            // matrix mult
    Matrix operator*(float scalar) const;                               // scalar mult right
    friend Matrix operator*(float scalar, const Matrix &m);             // scalar mult left
    float operator()(int i, int j) const;                               // paramthesis inedxing
    float &operator()(int i, int j);                                    //
    float operator[](int index) const;                                  // brackets indexing
    float &operator[](int k);                                           //
    friend std::ostream &operator<<(std::ostream &os, const Matrix &m); // pretty print matrix
    friend std::istream &operator>>(std::istream &is, Matrix &m);       // fill matrix with data
};

#endif // MATRIX_H