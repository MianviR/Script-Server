cmake_minimum_required(VERSION 3.10)

project(asioserver)

add_executable(server server.cpp)
add_executable(client client.cpp)
add_executable(server_beast server_beast.cpp)

target_include_directories(server PRIVATE "$ENV{HOME}/libs/cpp/boost_1_88_0")
target_include_directories(client PRIVATE "$ENV{HOME}/libs/cpp/boost_1_88_0")
target_include_directories(server_beast PRIVATE "$ENV{HOME}/libs/cpp/beast/include")
target_include_directories(server_beast PRIVATE "$ENV{HOME}/libs/cpp/boost_1_88_0")
