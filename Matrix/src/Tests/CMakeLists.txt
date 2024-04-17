find_package(Catch2 2 REQUIRED)

add_executable(Tests source/test.cpp)

target_link_libraries(Tests Matrix Array Catch2::Catch2)

target_include_directories(Tests PUBLIC ../Array/include ../Matrix/include)
