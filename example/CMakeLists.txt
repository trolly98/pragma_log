cmake_minimum_required(VERSION 3.8)

project(pragma_log_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(pragma_log_example
    main.cpp
    app_bundle.hpp
    app_bundle.cpp
)