#ifndef LAB1_SRC_ARRAY_INCLUDE_ARRAY_H
#define LAB1_SRC_ARRAY_INCLUDE_ARRAY_H
#include <cstddef>
#include <type_traits>

class Array {
  private:
    int* Values_ = nullptr;
    size_t Size_ = 0;
  public:

    template<bool isConst>
    class Iterator{
      public:
        using pointer = std::conditional_t<isConst, const int*, int*>;
        
        using reference = std::conditional_t<isConst, const int&, int&>;
      
      private:

        pointer Ptr_;

      public:

        Iterator() : Ptr_(nullptr) {}

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
        size_t operator-(const Iterator& Other) const {
            return Ptr_ - Other.Ptr_;
        }
        ~Iterator() {}
    };

    using CommonIterator = Iterator<false>;

    using ConstIterator = Iterator<true>;

    Array() = default;

    Array(size_t);
    
    Array(const Array&);
    
    Array(Array&&) noexcept;
    
    ~Array();
    
    Array& operator=(const Array&);
    
    Array& operator=(Array&&) noexcept;
    
    int& operator[](size_t);
    
    const int& operator[](size_t) const;
    
    size_t getSize() const;
    
    CommonIterator begin();
    
    CommonIterator end();

    ConstIterator cbegin() const;

    ConstIterator cend() const;
};
#endif