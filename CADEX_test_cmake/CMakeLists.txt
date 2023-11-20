cmake_minimum_required(VERSION 3.10)

project(CADEX_TEST_1 CXX)
set(CMAKE_CXX_STANDARD 20)

set(LIB_FILES Curve.cpp CurvesPrint.cpp)
set(OTHER_PROJ_FILES CurveGeneration.cpp main.cpp)

add_executable(cadex_test ${OTHER_PROJ_FILES} ${LIB_FILES})