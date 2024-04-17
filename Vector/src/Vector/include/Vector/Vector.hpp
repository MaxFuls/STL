#ifndef VECTORQUEQUE_SRC_VECTOR_INCLUDE_VECTOR_VECTOR_H
#define VECTORQUEQUE_SRC_VECTOR_INCLUDE_VECTOR_VECTOR_H
#include <memory>
#include <cstddef>
#include <iostream>
#include <initializer_list>
#include <concepts>
#include <iterator>

template<typename T, typename Allocator  = std::allocator<T>>
class Vector{
  
  private:
    
    size_t size_;
    
    size_t capacity_;
    
    Allocator alloc_;
    
    T* storage_;
     
    using AllocTraits = std::allocator_traits<Allocator>;
    
  public:
    
    using value_type = T;
    
    using allocator_type = Allocator;
    
    using size_type = size_t;
    
    using difference_type = std::ptrdiff_t;
    
    using reference = value_type&;
    
    using pointer = typename AllocTraits::pointer;
    
    using const_reference = const value_type&;
    
    using const_pointer = typename AllocTraits::const_pointer;
    
    using iterator = pointer;
    
    using const_iterator = const_pointer;
    
    using reverse_iterator = std::reverse_iterator<iterator>;
    
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
  private:

    template<typename ...Args>
    void create(Args&&... args){
      size_type i{0};
      try{
        for(; i < size_; ++i)
          AllocTraits::construct(alloc_, storage_ + i, std::forward<Args...>(args...));
        } catch(...){
          for(size_t j{0}; j < i; ++j)
            AllocTraits::destroy(alloc_, storage_ + j);
          AllocTraits::deallocate(alloc_, storage_, capacity_);
          throw;
      }
    }
  
  public:

    Vector() noexcept(noexcept(Allocator())) : size_(0), capacity_(0), alloc(Allocator()), storage_(nullptr) {}
    
    explicit Vector(const Allocator& alloc) noexcept : size_(0), capacity_(0), alloc_(alloc), storage_(nullptr)  {}
    
    Vector(size_type count, const T& value, const Allocator& alloc = Allocator()) : size_(count), capacity_(count),
          alloc_(alloc), storage_(AllocTraits::allocate(alloc_, count)) {create(value);}

    explicit Vector(size_type count, const Allocator& alloc = Allocator()) : size_(count), capacity_(count),
      alloc_(alloc), storage_(AllocTraits::allocate(alloc_, count)) {create();}
    
    template<std::input_iterator Iter>
    Vector(Iter first, Iter last, const Allocator& alloc = Allocator()) : size_(std::distance(first, last)),
      capacity_(size_), alloc_(alloc), storage_(AllocTraits::allocate(alloc_, size_)) {
        size_type i{0};
        try{
            for(; i < size_ && first != last; ++i, ++first)
                AllocTraits::construct(alloc_, storage_ + i, *first);
        } catch(...){
            for(size_t j{0}; j < i; ++j)
              AllocTraits::destroy(alloc_, storage_ + j);
            AllocTraits::deallocate(alloc_, storage_, capacity_);
            throw;
        }
    }
    
    Vector(const Vector& other) :
      Vector(other.cbegin(), other.cend(), AllocTraits::select_on_container_copy_construction(other.alloc_)) {}
      
    Vector(const Vector& other, const Allocator& alloc) : Vector(other.cbegin(), other.cend(), alloc) {}
    
    Vector(Vector&& other) noexcept : size_(other.size_), capacity_(other.capacity_),
      alloc_(std::move(other.alloc_)), storage_(other.storage_){
        other.size_ = 0;
        other.capacity_ = 0;
        other.storage_ = nullptr;
    }
    
    Vector(Vector&& other, const Allocator& alloc) : Vector(alloc) {
      if(alloc != other.get_allocator()){
        auto TmpVector = Vector(std::move_iterator(other.begin()), std::move_iterator(other.end()), alloc); 
        swap(TmpVector);
        capacity_ = other.capacity_;
      } else {
        swap(other);
      }
      other.clear();
    } 
    
    Vector(const std::initializer_list<T>& init, const Allocator& alloc = Allocator()) : 
      Vector(std::move_iterator(init.begin()), std::move_iterator(init.end()), alloc) {}

    ~Vector() {
      for(size_type i{0}; i < size_; ++i)
        AllocTraits::destroy(alloc_, storage_ + i);
      AllocTraits::deallocate(alloc_, storage_, capacity_);
    }

    Vector& operator=(const Vector& other) {
      if(other == *this) return *this;
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      // if(AllocTraits::propagate_on_container_copy_assignment::value){
      //   auto OldAlloc = alloc_;
      //   auto TmpVector = Vector(other.cbegin(), other.cend(), other.alloc_);
      //   swap(TmpVector);
      //   if(!AllocTraits::is_always_equal::value && alloc_ != other.get_allocator()){
      //     TmpVector.alloc_ = OldAlloc;
      //     alloc_ = other.alloc_;
      //   }
      // } else {
      //   auto TmpVector = Vector(other.cbegin(), other.cend(), alloc_);
      //   swap(TmpVector);
      // }
      // return *this;
    }
    
    Vector& operator=(Vector&& other)
      noexcept(AllocTraits::propogate_on_container_move_assignment::value || AllocTraits::is_always_equal::value) {
      if(AllocTraits::propogate_on_container_move_assignment::value){
        swap(other);
        if(!AllocTraits::propagate_on_container_swap::value)
          std::swap(alloc_, other.alloc_);
      }
      else{
        if(!AllocTraits::is_always_equal::value && alloc_ != other.get_allocator()){
          auto TmpVector = Vector(std::move_iterator(other.begin()), std::move_iterator(other.end()), alloc_);
          swap(TmpVector);
        } else 
          swap(other);
      }
        return *this;
    }

    void swap(Vector& other)
      noexcept(AllocTraits::propagate_on_container_swap::value || AllocTraits::is_always_equal::value) {
      std::swap(size_, other.size_);
      std::swap(capacity_, other.capacity_);
      std::swap(storage_, other.storage_);
      if(AllocTraits::propagate_on_container_swap::value)
        std::swap(alloc_, other.alloc_);
    }

    void reserve(size_type newcap) {
      if(newcap < capacity_) return;
      pointer NewArr = AllocTraits::allocate(alloc_, newcap);
      size_type i{0};
      try{
        for(; i < size_; ++i)
          AllocTraits::construct(alloc_, NewArr + i, std::move_if_noexcept(storage_[i]));
        capacity_ = newcap;
        for(size_type j{0}; j < size_; ++j)
          AllocTraits::destroy(alloc_, storage_ + j);
        AllocTraits::deallocate(alloc_, storage_, capacity_);
        storage_ = NewArr;

      } catch(...){
        for(size_type j{0}; j < i; ++j)
          AllocTraits::destroy(alloc_, NewArr + j);
        AllocTraits::deallocate(alloc_, NewArr, newcap);
      }
    }

    void clear() noexcept {
      for(size_type i{0}; i < size_; ++i){
        AllocTraits::destroy(alloc_, storage_ + i);
      }
      size_ = 0;
    }

    template<typename ...Args>
    iterator emplace(const_iterator pos, Args&&... args){
      auto RealPos = std::distance(cbegin(), pos);
      if(empty()){
        reserve(1);
        try{
          AllocTraits::construct(alloc_, storage_, std::forward<Args...>(args...));
          ++size_;
        } catch(...) {
          AllocTraits::destroy(alloc_, storage_);
          throw;
        }
      } else {
        if(size_ == capacity_){
          reserve(capacity_*2);
        }
        size_type i = size_;
        try{
          AllocTraits::construct(alloc_, storage_ + size_, std::forward<Args...>(args...));
          for(; i != RealPos; --i){
            *(storage_ + i) = std::move_if_noexcept(*(storage_ + i - 1));
          }
          *(storage_ + RealPos)  = T(std::forward<Args...>(args...));
          ++size_;
        } catch(...) {
          for(size_type j = i; i < size_; ++j)
            *(storage_ + j + 1) = std::move_if_noexcept(*(storage_ + j));
          AllocTraits::destroy(alloc_, storage_ + size_);
          throw;
        }
      }
      return std::next(begin(), RealPos);
    }
    
    template<typename ...Args>
    void emplace_back(Args&&... args) {
      emplace(end(), std::forward<Args...>(args...));
    }

    void push_back(const T& Value) { emplace_back(Value);}

    void push_back(T&& Value) { emplace_back(std::move(Value));}

    reference operator[](size_type pos) { return *(storage_ + pos);}

    const_reference operator[](size_type pos) const { return *(storage_ + pos);}

    iterator erase(const_iterator pos) {
      auto first = std::distance(cbegin(), pos);
      auto NewPos = first;
      if(empty()){
        return end();
      }
      else{
        try{
          for(; first < size_ - 1; ++first)
            *(storage_ + first) = std::move(*(storage_ + first + 1));
          --size_;
          AllocTraits::destroy(alloc_, storage_ + size_);
        } catch(...) {

          throw;
        }
      }
      return iterator(storage_ + NewPos); 
    }

    iterator erase(const_iterator first, const_iterator last){
      
    }

    void pop_back() { erase(end());}

    void pop_front( erase(begin());)

    iterator insert(const_iterator pos, const T& Value) { return emplace(pos, Value);}

    iterator insert(const_iterator pos, T&& Value) { return emplace(pos, std::move(Value));}

    reference front() {return *storage_;}

    reference back() { return *(storage_ + size_ -1);}

    size_type size() const { return size_;}

    size_type capacity() const {return capacity_;}

    allocator_type get_allocator() const {return alloc_;}

    bool empty() const { return size_ == 0; }
    
    iterator begin() { return iterator(storage_);}
    
    iterator end() { return iterator(storage_ + size_);}
    
    const_iterator cbegin() const { return const_iterator(storage_);}
    
    const_iterator cend() const { return const_iterator(storage_ + size_);}

    reverse_iterator rbegin() { return reverse_iterator(storage_);}

    reverse_iterator rend() { return reverse_iterator(storage_ + size_);}

    const_reverse_iterator crbegin() const { return const_reverse_iterator(storage_);}

    const_reverse_iterator crend() const { return const_reverse_iterator(storage_ + size_);}

    
};

#endif
