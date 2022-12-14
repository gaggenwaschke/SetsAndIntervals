# A library to make C++ understand math

[![gcc-11](https://github.com/gaggenwaschke/SetsAndIntervals/actions/workflows/gcc-11.yaml/badge.svg)](https://github.com/gaggenwaschke/SetsAndIntervals/actions/workflows/gcc-11.yaml)
[![gcc-12](https://github.com/gaggenwaschke/SetsAndIntervals/actions/workflows/gcc-12.yaml/badge.svg)](https://github.com/gaggenwaschke/SetsAndIntervals/actions/workflows/gcc-12.yaml)
[![clang-13](https://github.com/gaggenwaschke/SetsAndIntervals/actions/workflows/clang-13.yaml/badge.svg)](https://github.com/gaggenwaschke/SetsAndIntervals/actions/workflows/clang-13.yaml)
[![clang-14](https://github.com/gaggenwaschke/SetsAndIntervals/actions/workflows/clang-14.yaml/badge.svg)](https://github.com/gaggenwaschke/SetsAndIntervals/actions/workflows/clang-14.yaml)

# Features

This library is build on C++ std lib types.
The library currently supports the following features, with point of customization for each:
- Sets (currently using std::tuple, but as sets. Maybe I will properly redefine sets and tuples later.)
- Element of
- Subsets
- Countability
- Infinity (infinite sets)
- Iterating finite and infinite sets
