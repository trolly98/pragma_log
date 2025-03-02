cmake_minimum_required(VERSION 3.8)

project(pragma_log_library LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(pragma_log 
    src/pragma_log.hpp
    src/logging_category.hpp
    src/debug_logger.hpp
)