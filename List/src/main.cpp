#include <list>
#include <iostream>
#include <iterator>
#include "List/include/List/List.h"

// template<typename Iter>
// struct move_if_noexcept_iterator{
//   Iter iter;
//   move_if_noexcept_iterator(Iter iter) : iter(iter) {}
//   decltype(auto) operator*() {
//     return std::move_if_noexcept(*iter);
//   }
// };

// struct A {
// 	int a = 1;
// 	A(int a) : a(a) {}
// 	A(const A& other) : a(other.a) {} 
// 	A(A&& other) {
// 		std::swap(a, other.a);
// 	}
// };

// struct B {
// 	int b = 1;
// 	B(int b) : b(b){}
// 	B(B&& other) noexcept {
// 		std::swap(b, other.b);
// 	}
// };
    
int main(){
	List<int> list;
        list.emplace_back(1);
        list.emplace_back(2);
        list.emplace_back(3);
        list.emplace_back(4);
        list.emplace_back(5);
        list.emplace_back(6);
        list.emplace_back(7);
        list.emplace_back(8);
        list.emplace_back(9);
        list.emplace_back(10);
        for(auto v : list)
        std::cout << v << '\n';
	return 0;
}
