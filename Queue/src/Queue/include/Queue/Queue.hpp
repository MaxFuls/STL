#include <deque>

template<typename T, typename Container = std::deque<T>>
class Queue{
  private:
  
    Container cont_;
  
  public:

    using container_type = Container;

    using value_type = Container::value_type;
    
    using size_type = Container::size_type;
    
    using reference = Container::reference;
    
    using const_reference = Container::const_reference;

    Queue() : Queue(Container()) {}

    explicit Queue(const Container& cont) : cont_(cont) {}

    explicit Queue(Container&&) : cont_(std::move(cont)) {}

    Queue(const Queue& other) : cont_(other.cont_) {}

    Queue(Queue&& other) : cont_(std::move(other.cont_)) {}

    template<typename Iter>
    Queue(Iter first, Iter last) : cont_(first, last) {}

    template<typename Alloc>
    Queue(const Alloc& alloc) : cont_(alloc) {}

    template<typename Alloc>
    Queue(const Container& cont, const Alloc& alloc) : cont_(cont, alloc){}

    template<typename Alloc>
    Queue(Container&& cont, const Alloc& alloc) : cont_(cont, alloc) {}

    template<typename Alloc>
    Queue(const Queue& other, const Alloc& alloc) : cont_(other.cont_, alloc) {}

    template<typename Alloc>
    Queue(Queue&& other, const Alloc& alloc) : cont_(std::move(other.cont_), alloc) {}

    template<typename Alloc, typename Iter>
    Queue(Iter first, Iter last, const Alloc& alloc) : cont_(first, last, alloc) {}

    ~Queue() {}

    Queue& operator=(const Queue& other) { cont_ = other.cont_;}

    Queue& operator=(Queue&& other) { cont_ = std::move(other.cont_);}

    reference front() { return cont_.front();}

    reference back() { return cont_.back();}

    bool empty() const { return cont_.empty();}

    size_type size() const { return cont_.size();}

    void push(const T& value) { cont_.push_back(value);}

    void push(T&& value) { cont_.push_back(std::move(value));}

    template<typename ...Args>
    decltype(auto) emplace(Args... args) { cont_.emplace_back(std::forward<Args...>(args...));}

    void pop() { cont_.pop_front();}

    void swap(Queue& other) noexcept(noexcept(swap(cont_, other.cont_))) { swap(cont_. other.cont_);}

    
};