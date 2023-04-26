cmake_minimum_required(VERSION 3.25)
project(untitled7)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/include)

include_directories(/usr/local/include/nlohmann)

add_executable(untitled7 main.cpp)

set(CMAKE_OSX_ARCHITECTURES x86_64)

target_link_libraries(untitled7 curl)

