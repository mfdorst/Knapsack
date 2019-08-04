//===-- KnapsackDPSolver.cpp - Solve by Dynamic Programming ---------------===//
//
// Author: Michael Dorst
//
//===----------------------------------------------------------------------===//
/// \file
/// This file contains the KnapsackDPSolver class, which is responsible for
/// solving 0/1 knapsack problems using Dynamic Programming.
//===----------------------------------------------------------------------===//

#include "KnapsackDPSolver.h"

void KnapsackDPSolver::Solve(KnapsackInstance *instance_,
                             KnapsackSolution *solution_) {

  instance = instance_;
  solution = solution_;

  size_t itemCount = instance->GetItemCnt();
  size_t capacity = instance->GetCapacity();

  // Initialize solutionTable as a 2D ItemCount x Capacity matrix of empty
  // solutions
  solutionTable = std::move(std::vector<std::vector<KnapsackSolution>>(
      itemCount,
      std::vector<KnapsackSolution>(capacity, KnapsackSolution(instance))));

  // Initialize the first row of solutions to 0
}
