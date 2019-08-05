//===-- KnapsackBTSolver.cpp - Solve by Backtracking ----------------------===//
//
// Author: Michael Dorst
//
//===----------------------------------------------------------------------===//
/// \file
/// This file contains the KnapsackBTSolver class, which is responsible for
/// solving 0/1 knapsack problems using Backtracking.
//===----------------------------------------------------------------------===//

#include "KnapsackBTSolver.h"
#include "Time.h"

void KnapsackBTSolver::Solve(KnapsackInstance *instance_,
                             KnapsackSolution *solution_) {

  startTime = getTime();

  instance = instance_;
  bestSolution = solution_;
  currentSolution = new KnapsackSolution(instance);

  findSolutions(1);
}

/// Find solutions recursively.
/// Stops searching early if the solution weight exceeds the knapsack capacity.
/// \param itemNum The item currently under consideration
void KnapsackBTSolver::findSolutions(size_t itemNum) {

  // Check if time has run out
  if (timeSince(startTime) > maxDuration) {
    return;
  }

  // These are static so that the getters are only invoked once
  static size_t capacity = instance->GetCapacity();
  static uint32_t itemCount = instance->GetItemCnt();

  static uint32_t weight = 0;

  if (itemNum > itemCount) {

    int32_t currentvalue = currentSolution->ComputeValue();
    int32_t bestValue = bestSolution->GetValue();

    if (currentvalue > bestValue) {
      bestSolution->Copy(currentSolution);
    }
    return;
  }

  currentSolution->TakeItem(itemNum);
  findSolutions(itemNum + 1);
  currentSolution->DontTakeItem(itemNum);
  findSolutions(itemNum + 1);
}
