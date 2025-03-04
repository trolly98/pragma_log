cmake_minimum_required(VERSION 3.8)

project(pragma_log LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(pragma_log INTERFACE)

target_include_directories(pragma_log INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
