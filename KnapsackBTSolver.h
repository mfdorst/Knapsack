//===-- KnapsackBTSolver.h - Solve by Backtracking --------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===----------------------------------------------------------------------===//
/// \file
/// This file contains the KnapsackBTSolver class, which is responsible for
/// solving 0/1 knapsack problems using Backtracking.
//===----------------------------------------------------------------------===//

#ifndef KNAPSACKBTSOLVER_H
#define KNAPSACKBTSOLVER_H

#include "knapsack.h"

class KnapsackBTSolver {

  KnapsackInstance *instance;
  KnapsackSolution *currentSolution;
  KnapsackSolution *bestSolution;
  std::chrono::high_resolution_clock::time_point startTime;
  std::chrono::duration<double> maxDuration;
  bool outOfTime;

  void findSolutions(size_t itemNum);

public:
  KnapsackBTSolver()
      : instance(nullptr), currentSolution(nullptr), bestSolution(nullptr),
        maxDuration(std::chrono::seconds(3)), outOfTime(false) {}

  void Solve(KnapsackInstance *instance, KnapsackSolution *solution);
};

#endif // KNAPSACKBTSOLVER_H
