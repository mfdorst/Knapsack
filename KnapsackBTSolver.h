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

class KnapsackBTSolver : public KnapsackBFSolver {

public:
  KnapsackBTSolver() = default;
  ~KnapsackBTSolver() = default;

  void Solve(KnapsackInstance *inst, KnapsackSolution *soln) override;
};

#endif // KNAPSACKBTSOLVER_H
