add_executable(Lab1 source/main.cpp)

target_link_libraries(Lab1 Matrix Array Utility)

target_include_directories(Lab1 PUBLIC ../Matrix/include ../Utility/include)
