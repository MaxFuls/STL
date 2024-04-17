#ifndef SRC_MATRIX_SOURCE_MATRIX_H
#define SRC_MATRIX_SOURCE_MATRIX_H
#include "Array/Array.h"
#include <iostream>

class Matrix {
  private:
    Array* Lines_ = nullptr;
    size_t LineAmount_ = 0;
  public:

    template<bool isConst>
    class Iterator{
      public:
        using pointer = std::conditional_t<isConst, const Array*, Array*>;
        
        using reference = std::conditional_t<isConst, const Array&, Array&>;
      
      private:

        pointer Ptr_;
      
      public:
        Iterator(pointer Ptr) : Ptr_(Ptr) {}
        
        Iterator& operator++() {
            ++Ptr_;
            return *this;
        }

        reference operator*() {
            return *Ptr_;
        }
        
        pointer operator->() {
            return Ptr_;
        }
        
        bool operator==(const Iterator& Other) const {
            return Ptr_ == Other.Ptr_;
        }
    };
    
    using CommonIterator = Iterator<false>;
    
    using ConstIterator = Iterator<true>;

    Matrix() = default;
    
    Matrix(size_t, const Array&);
    
    Matrix(const  Matrix&);
    
    Matrix(Matrix&&) noexcept;
    
    ~Matrix();
    
    Matrix& operator=(const Matrix&);
    
    Matrix& operator=(Matrix&&) noexcept;
    
    void insert(size_t, size_t, int);
    
    size_t getLineAmount() const;
    
    CommonIterator begin();
    
    CommonIterator end();
    
    ConstIterator cbegin() const;
    
    ConstIterator cend() const;
};

#endif