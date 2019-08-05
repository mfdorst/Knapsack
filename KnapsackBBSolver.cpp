//===-- KnapsackBBSolver.cpp - Solve by Branch and Bound ------------------===//
//
// Author: Michael Dorst
//
//===----------------------------------------------------------------------===//
/// \file
/// This file contains the KnapsackBBSolver class, which is responsible for
/// solving 0/1 knapsack problems using Branch and Bound.
//===----------------------------------------------------------------------===//

#include "KnapsackBBSolver.h"

KnapsackBBSolver::KnapsackBBSolver(enum UPPER_BOUND ub_) { ub = ub_; }

void KnapsackBBSolver::Solve(KnapsackInstance *instance_,
                             KnapsackSolution *solution_) {}
