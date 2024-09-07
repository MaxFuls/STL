#ifndef LIST_INCLUDE_LIST_LIST_H
#define LIST_INCLUDE_LIST_LIST_H
#include <memory>
#include <cstddef>
#include <iterator>
#include <limits>

template<typename Iter>
struct move_if_noexcept_iterator{
  Iter iter;
  move_if_noexcept_iterator(Iter iter) : iter(iter) {}

  decltype(auto) operator*() {
    return move_if_noexcept(*iter);
  }
};

template<typename T, typename Allocator = std::allocator<T>>
class List{
  public:

    using value_type = T;
  
    using allocator_type = Allocator;
    
    using size_type = size_t;
    
    using difference_type = std::ptrdiff_t;
    
    using reference = value_type&;
    
    using const_reference = const reference;
    
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer; 

  private:
    
    struct Node{

      Node* next_;
      
      Node* prev_;
      
      std::byte value_[sizeof(value_type)];

      Node() : next_(nullptr), prev_(nullptr) {}
      
      template<typename ...Args> 
      Node(Args&&... args) : next_(nullptr), prev_(nullptr) {
        new(value_) value_type(std::forward<Args>(args)...);
      }

      ~Node() {
        (*reinterpret_cast<pointer>(value_)).~value_type();
      }

    };
    
    template<bool isConst>
    class Iterator{
        
      public:

        using difference_type = std::ptrdiff_t;

        using value_type = T;

        using pointer = std::conditional_t<isConst, const value_type*, value_type*>;

        using reference = std::conditional_t<isConst, const value_type&, value_type&>;

        using iterator_category = std::bidirectional_iterator_tag;

        Iterator() : ptr_(nullptr) {}

        template<bool otherConst>
          requires (otherConst <= isConst)
        Iterator(const Iterator<otherConst>& other) : ptr_(other.ptr_) {}

        template<bool otherConst>
          requires (otherConst <= isConst)
        Iterator& operator=(const Iterator& other) { 
          ptr_ = other.ptr_;
          return *this;
        }

        Iterator& operator++(){
          ptr_ = ptr_->next_;
          return *this;
        }

        Iterator operator++(int){
          auto tmp = *this;
          ++(*this);
          return tmp;
        }

        reference operator*(){ return *(reinterpret_cast<pointer>(ptr_->value_));}

        bool operator==(const Iterator& other) const { return ptr_ == other.ptr_;}

        pointer* operator->() { return &(ptr_->value);}

        Iterator& operator--() {
          ptr_ = ptr_->prev_;
          return *this;
        }

        Iterator operator--(int) {
          auto tmp = *this;
          --(*this);
          return tmp;
        }

        friend class List;

      private:

        Node* ptr_;

        Iterator(Node* node) : ptr_(node) {} 

    };

    using NodeAllocator = typename std::allocator_traits<Allocator>::rebind_alloc<Node>;

    using AllocTraits = std::allocator_traits<NodeAllocator>;

    Node begin_;

    size_t size_;
    
    NodeAllocator alloc_;

    void link(Node& first, Node& second){
      first.next_ = &second;
      second.prev_ = &first;
    }

  public:

    using iterator = Iterator<false>;

    using const_iterator = Iterator<true>;

    using reverse_iterator = std::reverse_iterator<iterator>;

    using const_reverse_iterator = std::reverse_iterator<const_iterator>;


    List() : size_(0) {
      begin_.prev_ = &begin_;
      begin_.next_ = &begin_;
    }

    explicit List(const Allocator& alloc) : size_(0), alloc_(alloc) {
      begin_.prev_ = &begin_;
      begin_.next_ = &begin_;
    }

    List(size_type count, const T& value, const Allocator& alloc = Allocator()) : List(alloc) {
      try{
        for(size_type i = 0; i < count; ++ i)
          emplace_back(value);
      } 
      catch(...) {
        clear();
        throw;
      }
    }

    explicit List(size_type count, const Allocator& alloc = Allocator()) : List(count, T(), alloc) {}

    template<std::input_iterator Iter>
    List(Iter first, Iter last, const Allocator& alloc = Allocator()) : List(alloc) {
      try{
        for(; first != last; ++first)
        emplace_back(*first);
      } catch(...){
        clear();
        throw;
      }
    }

    List(std::initializer_list<T> init, const Allocator& alloc = Allocator()) : 
      List(std::move_iterator(init.begin_()), std::move_iterator(init.end()), alloc) {}

    List(const List& other) : List(other.begin_(), other.end(), 
      AllocTraits::select_on_container_copy_construction(other.get_allocator())) {}

    List(const List& other, const Allocator& alloc) : List(other.begin_(), other.end(), alloc) {}

    List(List&& other) noexcept : size_(other.size_), begin_(std::move(other.begin_)), alloc_(std::move(other.alloc_)) {
      other.size_ = 0;
    }

    List(List&& other, const Allocator& alloc) noexcept : 
      List(alloc == other.get_allocator() 
           ? std::move(other) 
           : (move_if_noexcept_iterator(other.begin_()), move_if_noexcept_iterator(other.end()), alloc)) {}

    ~List() { clear(); }

    List& operator=(const List& other) {
      if(other == *this) return *this;
      List copy(begin_(), end(), alloc_);
      if(AllocTraits::propogate_on_container_copy_assignment::value && alloc_ != other.get_allocator()){
        clear();
        alloc_ = other.alloc_;
      }
      try {
        clear();
        List tmp(other.begin_(), other.end(), alloc_);
        swap(tmp);

      } catch(...) {
        swap(copy);
        throw;
      }
      return *this;
    }

    List& operator=(List&& other) {
      if(other == *this) return *this;
      List copy(begin_(), end(), alloc_);
      if(AllocTraits::propogate_on_container_move_assignment::value){
        if(alloc_ == other.get_allocator()){
          begin_ = std::move(other.begin_);
          return *this;
        } else {
          clear();
          alloc_ = other.alloc_;
        }
      }
      try {
        clear();
        List tmp(move_if_noexcept_iterator(other.begin_()), move_if_noexcept_iterator(other.end()), alloc_);
        swap(tmp);
      } catch(...) {
        swap(copy);
        throw;
      }
      return *this;
    }

    void swap(List& other) noexcept(AllocTraits::is_always_equal::value) {
      if(AllocTraits::propogate_on_container_swap::value && alloc_ != other.ger_allocator())
        std::swap(alloc_, other.alloc_);
      std::swap(begin_, other.begin_);
      std::swap(size_, other.size_);
    }

    void clear() {
      auto ptr1 = begin_.next_;
      auto ptr2 = ptr1->next_;
      for(; ptr1 != &begin_; ptr2 = ptr2->next_){
        AllocTraits::destroy(alloc_, ptr1);
        AllocTraits::deallocate(alloc_, ptr1, 1);
        ptr1 = ptr2;
        }
      size_ = 0;
      }
  
    template<typename ...Args>
    iterator emplace(const_iterator pos, Args&&... args){
      auto ptr = AllocTraits::allocate(alloc_, 1);
      try{
        AllocTraits::construct(alloc_, ptr, std::forward<Args>(args)...);
      } catch(...) {
        AllocTraits::deallocate(alloc_, ptr, 1);
        throw;
      }
      auto prev_ = pos.ptr_->prev_;  
      link(*ptr, *(pos.ptr_));
      link(*prev_, *ptr);
      ++size_;
      return iterator(ptr);
    }
    
    template<typename ...Args>
    void emplace_back(Args&&... args) {
      emplace(end(), std::forward<Args>(args)...);
    }

    template<typename ...Args>
    void emplace_front(Args&&... args){
      emplace(begin_(), std::forward<Args>(args)...);
    }

    void push_back(const T& value){ emplace_back(value);}

    void  push_back(T&& value) { emplace_back(std::move(value));}

    void push_front(const T& value) {emplace_front(value);}

    void emplace_front(T&& value) {emplace_front(std::move(value));}

    iterator insert(const_iterator pos, const T& value) { return emplace(pos, value);}

    iterator insert(const_iterator pos, T&& value) {return emplace(pos, std::move(value));}

    iterator insert(const_iterator pos, size_type count, const T& value) {}

    template<std::input_iterator InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last) {}

    iterator insert(const_iterator pos, std::initializer_list<T> inlist) {
      return insert(pos, std::move_iterator<decltype(inlist.begin_())>(inlist.begin_()),
                         std::move_iterator<decltype(inlist.begin_())>(inlist.end()));
    }

    iterator erase(const_iterator pos) {
      if(!empty() && pos != end()){
        auto prev_ = pos.ptr_->prev_;
        auto next_ = pos.ptr_->next_;
        link(*prev_, *next_);
        AllocTraits::destroy(alloc_, pos.ptr_);
        AllocTraits::deallocate(alloc_, pos.ptr_, 1);
        --size_;
        return iterator(next_);
      }
      return end();
    }

    iterator erase(const_iterator first, const_iterator last) {
      
    }

    reference front() { return *(begin_());}

    reference back() { return *(iterator(begin_.prev_));}

    iterator begin() {return iterator(begin_.next_);}

    iterator end() {return iterator(&begin_);}

    const_iterator cbegin() const { return const_iterator(begin_.next_);}

    const_iterator cend() const { return const_iterator(&begin_);}

    reverse_iterator rbegin() { return reverse_iterator(begin_());}

    reverse_iterator rend() { return reverse_iterator(end());}

    const_reverse_iterator crbegin() const { return const_reverse_iterator(cbegin());}

    const_reverse_iterator crend() const { return const_reverse_iterator(cend());}

    size_type size() const { return size_;}

    size_type max_size() const { return std::numeric_limits<difference_type>::max();}
    
    bool empty() const { return size() == 0;}

    NodeAllocator get_allocator() const {
      return alloc_;
    }

};

#endif