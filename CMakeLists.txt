cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

project(SetsAndIntervals VERSION 0.1.0 LANGUAGES CXX)

add_library(sets_and_intervals INTERFACE)
target_include_directories(sets_and_intervals INTERFACE ./src)

add_subdirectory(unit_test)
