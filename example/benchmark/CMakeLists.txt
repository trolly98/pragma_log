cmake_minimum_required(VERSION 3.8)

project(pragma_log_benchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_executable(pragma_log_benchmark
    main.cpp
)