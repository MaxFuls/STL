add_executable(Queue source/main.cpp)

target_include_directories(Queue PUBLIC ../Descriptor/include ../Queue/include ../Utility/include)

target_link_libraries(Queue Descriptor)
