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

class KnapsackDPSolver {
private:
  KnapsackInstance *instance;
  KnapsackSolution *solution;

  /// A 2-D array of dimensions ItemCount+1 x Capacity+1.
  /// Each cell stores the optimal solution for the capacity and item count
  /// indicated by its row and column.
  /// For example, `solutionTable[3][5]` will store the optimal solution for
  /// a 0/1 knapsack problem with capacity 3 and item count 5.
  std::vector<std::vector<KnapsackSolution>> solutionTable;

public:
  KnapsackDPSolver() : instance(nullptr), solution(nullptr) {}

  void Solve(KnapsackInstance *instance, KnapsackSolution *solution);
};

#endif // KNAPSACKDPSOLVER_H
