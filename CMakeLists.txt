cmake_minimum_required(VERSION 3.24)
project(password_manager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

add_executable(password_manager main.cpp bigint/operators.cpp bigint/ftype.cpp bigint/BigInt.cpp bigint/bigmath.cpp InputReader.cpp primes/PrimeHandler.cpp)