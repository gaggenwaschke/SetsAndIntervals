cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(SetsAndIntervals VERSION 0.1.0 LANGUAGES CXX)

set(CXX_STANDARD_REQUIRED On)

add_library(sets_and_intervals INTERFACE)
set_target_properties(sets_and_intervals PROPERTIES CMAKE_CXX_STANDARD 20)
target_compile_features(sets_and_intervals INTERFACE cxx_std_20)
target_include_directories(sets_and_intervals INTERFACE ./src/public)

add_subdirectory(unit_test)
