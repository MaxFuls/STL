#include "List/List.h"
#include <gtest/gtest.h>


TEST(list, constructors){

    List<int> list;
    list.emplace(list.begin(), 10);
    list.emplace(list.begin(), 5);
    list.emplace_back(15);
    for(auto v : list)
        std::cout << v << '\n';
    std::cout << '\n';
    list.erase(list.begin());
    for(auto v : list)
        std::cout << v << '\n';
    List<int> lissst(8, 10);
    for(auto v : lissst)
        std::cout << v << '\n';
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

}


int main(int args, char** argv){
    testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}
