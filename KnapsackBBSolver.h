//===-- KnapsackBBSolver.h - Solve by Branch and Bound ----------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===----------------------------------------------------------------------===//
/// \file
/// This file contains the KnapsackBBSolver class, which is responsible for
/// solving 0/1 knapsack problems using Branch and Bound.
//===----------------------------------------------------------------------===//

#ifndef KNAPSACKBBSOLVER_H
#define KNAPSACKBBSOLVER_H

#include "knapsack.h"

class KnapsackBBSolver {
protected:
  enum UPPER_BOUND upperBound;
  KnapsackInstance *instance;
  KnapsackSolution *currentSolution;
  KnapsackSolution *bestSolution;
  std::chrono::high_resolution_clock::time_point startTime;
  std::chrono::duration<double> maxDuration;
  bool outOfTime;

  void findSolutions(size_t itemNum);

public:
  explicit KnapsackBBSolver(enum UPPER_BOUND upperBound)
      : instance(nullptr), currentSolution(nullptr), bestSolution(nullptr),
        maxDuration(std::chrono::seconds(3)), outOfTime(false),
        upperBound(upperBound) {}

  ~KnapsackBBSolver() = default;

  void Solve(KnapsackInstance *instance, KnapsackSolution *solution);
};

#endif // KNAPSACKBBSOLVER_H
