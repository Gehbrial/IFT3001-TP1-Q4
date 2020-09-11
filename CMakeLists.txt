cmake_minimum_required(VERSION 3.12)
project(IFT3001_TP1_Q4)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(IFT3001_TP1_Q4
        entier.cpp
        entier.hpp
        fermeture_transitive.cpp
        fermeture_transitive.hpp
        matrice.cpp
        matrice.hpp
        tests_fermeture_transitive.cpp)
