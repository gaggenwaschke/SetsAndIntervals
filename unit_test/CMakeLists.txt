cmake_minimum_required(VERSION 3.18 FATAL_ERROR)

include(FetchContent)
fetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.2.1
)
fetchContent_MakeAvailable(Catch2)

add_executable(unit_test
    math/integral_iterator.cpp
    math/interval.cpp
    math/numberspaces.cpp
    math/operations.cpp
    math/set/flattening_view.cpp
    math/set/set.cpp)
    
target_link_libraries(unit_test PRIVATE
    sets_and_intervals
    Catch2::Catch2WithMain)
