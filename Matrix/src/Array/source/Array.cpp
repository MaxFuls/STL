#include "Array/Array.h"
#include <algorithm>
#include <stdexcept>

Array::Array(size_t Size) : Size_(Size), Values_(new int[Size]{0}) {}

Array::Array(const Array& Other) : Size_(Other.Size_), Values_(new int[Size_]) {
    std::copy(Other.Values_, Other.Values_ + Size_, Values_);
}

Array::Array(Array&& Other) noexcept : Size_(Other.Size_), Values_(Other.Values_) {
    Other.Size_ = 0;
    Other.Values_ = nullptr;
}

Array& Array::operator=(Array&& Other) noexcept {
    std::swap(Size_, Other.Size_);
    std::swap(Values_, Other.Values_);
    return *this;
}

Array& Array::operator=(const Array& Other){
    return *this = Array(Other);    
}

Array::~Array(){
    delete[] Values_;
}

size_t Array::getSize() const {
    return Size_;
}

int& Array::operator[](size_t Index) {
    if(Index >= Size_)
        throw std::out_of_range("index more then size");
    return Values_[Index];
}

const int& Array::operator[](size_t Index) const {
    if(Index >= Size_)
        throw std::out_of_range("index more then size");
    return Values_[Index];
}

Array::CommonIterator Array::begin() {
    return CommonIterator(Values_);
}
Array::CommonIterator Array::end() {
    return CommonIterator(Values_ + Size_);
}

Array::ConstIterator Array::cbegin() const {
    return ConstIterator(Values_);
}

Array::ConstIterator Array::cend() const {
    return ConstIterator(Values_ + Size_);
}