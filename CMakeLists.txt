cmake_minimum_required(VERSION 3.24)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
#set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc CACHE PATH "" FORCE)
set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++ CACHE PATH "" FORCE)
project(password_manager)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -pedantic")
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)

add_executable(password_manager main.cpp bigint/operators.cpp structures/ftype.cpp bigint/BigInt.cpp bigint/bigmath.cpp InputReader.cpp primes/PrimeHandler.cpp managers/Password.cpp managers/Date.cpp structures/PasswordCollection.cpp db/DBCore.cpp)

add_subdirectory(libpqxx)
target_link_libraries(password_manager pqxx)