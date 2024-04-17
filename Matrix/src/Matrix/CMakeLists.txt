add_library(Matrix ./source/Matrix.cpp ./source/MatrixUtil.cpp)

target_include_directories(Matrix PUBLIC include ../Array/include ../Utility/include)
