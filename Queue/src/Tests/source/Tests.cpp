#include "Descriptor/Descriptor.h"
#include <gtest/gtest.h>
#include <string>
#include <sstream>
#include <iostream>

TEST(descriptor, input_operator){
    Descriptor desc1, desc2, desc3;
    std::stringstream ss1("qwerty/123/321 ytrewq/321/123 ");
    ss1 >> desc1 >> desc2;;
    ASSERT_EQ(desc1.getId(), "qwerty");
    ASSERT_EQ(desc1.getTa(), 123);
    ASSERT_EQ(desc1.getTs(), 321);
    ASSERT_EQ(desc2.getId(), "ytrewq");
    ASSERT_EQ(desc2.getTa(), 321);
    ASSERT_EQ(desc2.getTs(), 123);
    std::stringstream ss2("qwerty/qw/e-1");
    ss2 >> desc3;
    ASSERT_EQ(ss2.fail(), true);
    std::stringstream ss3("qwerty/0/0 qwerty/1/2 ");
    ss3 >> desc3;
    ASSERT_EQ(desc3.getTa(), 1);
    ASSERT_EQ(desc3.getTs(), 2);
}

int main(int args, char** argv){
    testing::InitGoogleTest(&args, argv);
    return RUN_ALL_TESTS();
}