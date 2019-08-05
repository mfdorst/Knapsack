cmake_minimum_required(VERSION 3.14)
project(Knapsack)

set(CMAKE_CXX_STANDARD 14)

add_executable(Knapsack knapsack.cpp knapsack.h KnapsackDPSolver.cpp KnapsackDPSolver.h Time.h KnapsackBTSolver.cpp KnapsackBTSolver.h Time.cpp)