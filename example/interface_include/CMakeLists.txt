cmake_minimum_required(VERSION 3.8)

project(pragma_log_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")

include_directories(../../../pragma_log/include ${CMAKE_BINARY_DIR}/pragma_log_build)

add_executable(pragma_log_example
    main.cpp
)


