#ifndef LAB1_SRC_MATRIX_INCLUDE_MATRIXUTIL_H
#define LAB1_SRC_MATRIX_INCLUDE_MATRIXUTIL_H
#include "Matrix/Matrix.h"
#include <iostream>

std::ostream& printMatrix(std::ostream&, const Matrix&);
Matrix swapMinMax(const Matrix&);
std::istream& scanMatrix(Matrix&, std::istream&, std::ostream&);

#endif