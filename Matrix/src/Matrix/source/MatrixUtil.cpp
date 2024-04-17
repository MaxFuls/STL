#include "Matrix/MatrixUtil.h"
#include "Utility/Utility.h"
#include <iostream>
#include <limits>

std::ostream& printMatrix(std::ostream& Stream, const Matrix& Matrix) {
    for(auto begin = Matrix.cbegin(), end = Matrix.cend(); begin != end; ++begin){
        for(auto first = begin->cbegin(), last = begin->cend(); first != last; ++first ){
            Stream << *first << " ";
        }
        Stream << '\n';
    }
    return Stream;
}
std::istream& scanMatrix(Matrix& Matrix_, std::istream& In, std::ostream& Out) {

    auto Predicat = [](int a){return a > 0;};
    Out << "enter number of lines\n";
    int Lines = getValue<int>(In, Out, Predicat);
    Array LineSizes(Lines);
    Out << "enter number of elements in each line\n";
    for(size_t i{0}; i < Lines; ++i){
        LineSizes[i] = getValue<int>(In, Out, Predicat);
    }
    Matrix TmpMatrix(Lines, LineSizes);
    Out << "enter elemenets\n";
    for(size_t i{0}; i < Lines; ++i){
        for(size_t j{0}; j < LineSizes[i]; ++j){
            TmpMatrix.insert(i, j, getValue<int>(In, Out));
        }
    }
    Matrix_ = std::move(TmpMatrix);
    return In;
}
