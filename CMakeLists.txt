cmake_minimum_required(VERSION 3.27)
project(ECC_Capstone)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--stack,16000000000")

add_executable(ECC_Capstone main.cpp
        elliptic_curve.cpp
        elliptic_curve.h
        ecc.cpp
        ecc.h
)
