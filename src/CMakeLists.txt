cmake_minimum_required(VERSION 3.10)

project(asioserver)

set(BOOST_ROOT "$ENV{HOME}/libs/cpp/boost_1_88_0")
set(Boost_INCLUDE_DIR "${BOOST_ROOT}")
set(Boost_LIBRARY_DIR "${BOOST_ROOT}/stage/lib")
set(CMAKE_PREFIX_PATH "${Boost_LIBRARY_DIR}")

find_package(Boost 1.88 REQUIRED COMPONENTS filesystem system CONFIG)
link_directories($Boost_LIBRARY_DIR)

add_executable(server_beast server_beast.cpp)

target_include_directories(server_beast PRIVATE "$ENV{HOME}/libs/cpp/beast/include")
target_include_directories(server_beast PRIVATE "$ENV{HOME}/libs/cpp/boost_1_88_0")
target_include_directories(server_beast PRIVATE "/home/mianvi/libs/cpp/json/include")
target_include_directories(server_beast PRIVATE "/home/mianvi/libs/cpp/inja/include")
target_link_libraries(server_beast
	${Boost_FILESYSTEM_LIBRARY}
	${Boost_SYSTEM_LIBRARY}
)
