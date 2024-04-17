// #include "Vector/include/Vector/Vector.hpp"
#include <cstddef>
#include <typeinfo>
#include <iostream>
#include <memory>
#include <list>
#include <queue>
#include <vector>

struct A {
    int i = 0;
    A() = delete;
    A(int i) : i(i) {std::cout << "fuck\n";};
    A(const A&) {std::cout<< "blat\n";}
    friend std::ostream& operator<<(std::ostream&, const A&);
};
std::ostream& operator<<(std::ostream& o, const A& a){
    o<<a.i<<'\n';
    return o;
}

int main() {
    
    std::vector<int> v = {1, 2, 3, 4};
    auto iter = v.begin();
    ++iter;
    std::cout << *(v.erase(iter)) << '\n';
    return 0;
}