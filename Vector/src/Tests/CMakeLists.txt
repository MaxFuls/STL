find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(Tests source/Tests.cpp)
target_link_libraries(Tests ${GTEST_LIBRARIES})

target_include_directories(Tests PUBLIC ../Vector/include)
