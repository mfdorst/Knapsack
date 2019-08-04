//===-- KnapsackDPSolver.h - Solve by Dynamic Programming -------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===----------------------------------------------------------------------===//
/// \file
/// This file contains the KnapsackDPSolver class, which is responsible for
/// solving 0/1 knapsack problems using Dynamic Programming.
//===----------------------------------------------------------------------===//

#ifndef KNAPSACKDPSOLVER_H
#define KNAPSACKDPSOLVER_H

#include "knapsack.h"

/// Provides a solution for a 0/1 Knapsack Problem, using Dynamic Programming.
///
class KnapsackDPSolver {
private:
  KnapsackInstance *instance;
  KnapsackSolution *solution;

public:
  KnapsackDPSolver() : instance(nullptr), solution(nullptr) {}

  /// Solve a 0/1 Knapsack Problem using Dynamic Programming.
  /// \param instance The 0/1 Knapsack Problem to be solved
  /// \param [out] solution The solution to the 0/1 Knapsack Problem
  void Solve(KnapsackInstance *instance, KnapsackSolution *solution);
};

#endif // KNAPSACKDPSOLVER_H
