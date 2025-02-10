// MlpNetwork.h
#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4
#define EXPECTED_ROWS 28
#define EXPECTED_COLS 28

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit
{
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64, 128},
									{20, 64},
									{10, 20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64, 1},
								 {20, 1},
								 {10, 1}};

class MlpNetwork
{
private:
	Dense d0, d1, d2, d3;

public:
	MlpNetwork(const Matrix *weights, const Matrix *biases);
	digit operator()(const Matrix &m) const;
};

#endif // MLPNETWORK_H