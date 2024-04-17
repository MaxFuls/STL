#include "Utility//Utility.h"
#include "Matrix/Matrix.h"
#include "Matrix/MatrixUtil.h"
#include "Array/Array.h"
#include <iostream>

int main() {
    Matrix m1;
    try{
    scanMatrix(m1, std::cin, std::cout);
    } catch(std::runtime_error& re){
        std::cout << re.what() << std::endl;
        return 1;
    }
    printMatrix(std::cout, m1);
    return 0;
}