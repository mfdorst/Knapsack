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

class KnapsackBBSolver : public KnapsackBFSolver {
protected:
  enum UPPER_BOUND ub;

public:
  explicit KnapsackBBSolver(enum UPPER_BOUND ub_);

  ~KnapsackBBSolver() = default;

  void Solve(KnapsackInstance *inst, KnapsackSolution *soln) override;
};

#endif // KNAPSACKBBSOLVER_H
