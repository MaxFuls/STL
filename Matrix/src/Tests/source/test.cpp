#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "Array/Array.h"
#include "Matrix/Matrix.h"
#include <sstream>

TEST_CASE("Array"){
    SECTION("Constructors"){
        Array a1(2);
        REQUIRE(a1.getSize() == 2);
        REQUIRE_THROWS(Array(-1));
        Array a2(a1);
        REQUIRE(a2.getSize() == 2);
        Array a3(Array(3));
        REQUIRE(a3.getSize() == 3);
    }
    SECTION("Assignment operators"){
        Array a1(8);
        Array a2(3);
        a2 = a1;
        REQUIRE(a2.getSize() == 8);
        Array a3(1);
        a3 = std::move(a2);
        REQUIRE(a3.getSize() == 8);
    }
    SECTION("Operator []"){
        Array a1(10);
        a1[0] = 1;
        REQUIRE(a1[0] == 1);
        REQUIRE(a1[1] == 0);
    }
}
TEST_CASE("Matrix"){
    SECTION("Constructor"){
        Array a(3);
        a[0] = 1;
        a[1] = 2;
        a[2] = 3;
        Matrix m1(3, a);
        REQUIRE(m1.getLineAmount() == 3);   
        
        Matrix m2(4, a);
        
        a[0] = -1;
        REQUIRE_THROWS(Matrix(3, a));
    }
    SECTION("Copy and move constructors"){
        Array a(3);
        a[0] = 1;
        a[1] = 2;
        a[2] = 3;
        Matrix m1(3, a);
        Matrix m2(m1);
        REQUIRE(m2.getLineAmount() == 3);
        Matrix m3(std::move(m1));
        REQUIRE(m3.getLineAmount() == 3);
    }
    SECTION("Assignment ooperatrors"){
        Array a(3);
        a[0] = 1;
        a[1] = 2;
        a[2] = 3;
        Matrix m1(3, a);
        Matrix m2(2, a);
        m2 = m1;
        REQUIRE(m2.getLineAmount() == 3);
        Matrix m3(1, a);
        m3 = std::move(m1);
        REQUIRE(m3.getLineAmount() == 3);
    }
    SECTION("Insert method"){
        Array a(3);
        a[0] = a[1] = a[2] = 1;
        Matrix m1(3, a);
        m1.insert(0, 0, 1);
        m1.insert(1, 0, 2);
        m1.insert(2, 0, 3);
        REQUIRE_THROWS(m1.insert(-1, 0, 1));
        REQUIRE_THROWS(m1.insert(3, 0, 1));
        REQUIRE_THROWS(m1.insert(0, -1, 1));
        REQUIRE_THROWS(m1.insert(0, 3, 1));
    }
    SECTION("Sort method"){
        Array a(3);
        a[0] = a[1] = a[2] = 3;
        Matrix m(3, a);
        m.insert(0, 0, 1);
        m.insert(0, 1, 2);
        m.insert(0, 2, 3);
        m.insert(1, 0, 3);
        m.insert(1, 1, 2);
        m.insert(1, 2, 1);
        m.insert(2, 0, 2);
        m.insert(2, 1, 3);
        m.insert(2, 2, 1);
    }
}