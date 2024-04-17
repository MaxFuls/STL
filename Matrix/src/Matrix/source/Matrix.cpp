#include "Matrix/Matrix.h"
#include "Array/Array.h"
#include <cstddef>
#include <stdexcept>
#include <algorithm>

Matrix::Matrix(size_t LineAmount, const Array& LinesSizes) : LineAmount_(LineAmount),Lines_(new Array[LineAmount]) {
    size_t i{0};
    try{
        for(; i < LinesSizes.getSize() && i < LineAmount_; ++i)
            Lines_[i] = Array(LinesSizes[i]);
        for(; i < LineAmount_; ++i)
            Lines_[i] = Array(1);
    }catch(...){
        delete[] Lines_;
        throw;
    }
}

Matrix::Matrix(const Matrix& Other) : LineAmount_(Other.LineAmount_), Lines_(new Array[Other.LineAmount_]) {
    std::copy(Other.Lines_, Other.Lines_ + LineAmount_, Lines_);
}

Matrix::Matrix(Matrix&& Other) noexcept : LineAmount_(Other.LineAmount_), Lines_(Other.Lines_) {
    Other.Lines_ = nullptr;
    Other.LineAmount_ = 0;
}

Matrix& Matrix::operator=(Matrix&& Other) noexcept{
    std::swap(LineAmount_, Other.LineAmount_);
    std::swap(Lines_, Other.Lines_);
    return *this;
}

Matrix& Matrix::operator=(const Matrix& Other) {
    return *this = Matrix(Other);
}

Matrix::~Matrix() {
    delete[] Lines_;
}

void Matrix::insert(size_t Line, size_t Column, int Value) {
    if(Line < 0 || Line >= LineAmount_ || Column < 0 || Column >= Lines_[Line].getSize())
        throw std::invalid_argument("invalid index");
    Lines_[Line][Column] = Value;
}

size_t Matrix::getLineAmount() const {
    return LineAmount_;
}

Matrix::CommonIterator Matrix::begin() {
    return Matrix::CommonIterator(Lines_);
}

Matrix::CommonIterator Matrix::end() {
    return Matrix::CommonIterator(Lines_ + LineAmount_);
}

Matrix::ConstIterator Matrix::cbegin() const {
    return Matrix::ConstIterator(Lines_);
}

Matrix::ConstIterator Matrix::cend() const {
    return Matrix::ConstIterator(Lines_ + LineAmount_);
}