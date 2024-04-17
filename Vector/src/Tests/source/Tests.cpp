#define CATCH_CONFIG_MAIN
#include <gtest/gtest.h>
#include <Vector/Vector.hpp>
#include <memory>
#include <cstddef>
#include <vector>

TEST(vector, constructors){
    Vector<int> v1;
    ASSERT_EQ(v1.capacity(), 0);
    ASSERT_EQ(v1.size(), 0);
    ASSERT_EQ(v1.get_allocator(), std::allocator<int>());
    // Vector<int, Allocator<int>> v2(alloc);
    // ASSERT_EQ(v2.capacity(), 0);
    // ASSERT_EQ(v2.size(), 0);
    //ASSERT_EQ(v2.get_allocator(), alloc);
}

TEST(vector, move_constructors){
    Vector<int> v1{1, 2, 3};
    Vector<int> v2(std::move(v1));
    auto iter = v2.begin();
    ASSERT_EQ(v2.front(), 1);
    ASSERT_EQ(*(++iter), 2);
    ASSERT_EQ(v2.back(), 3);
    ASSERT_EQ(v1.empty(), true);
}

TEST(vector, copy_assignment){
    Vector<int> v1{1, 2, 3};
    Vector<int> v2{4, 5, 6};
    v2 = v1;
    auto iter = v2.begin();
    ASSERT_EQ(v2.front(), 1);
    ASSERT_EQ(*(++iter), 2);
    ASSERT_EQ(v2.back(), 3);
}

TEST(vector, move_assignment){


}

TEST(vector, emplace){
    Vector<int> v;
    auto iter = v.begin();
    v.emplace(v.begin(), 1);
     
}

TEST(vector, pop_back){
    Vector<int> v{1, 2, 3, 4};

}

TEST(vector, emplace_back){
    Vector<int> v;
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    auto first = v.begin();
}

int main(int args, char** argv){
    testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}