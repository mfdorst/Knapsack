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
#include "Time.h"

void KnapsackBBSolver::Solve(KnapsackInstance *instance_,
                             KnapsackSolution *solution_) {

  startTime = getTime();

  instance = instance_;
  bestSolution = solution_;
  currentSolution = new KnapsackSolution(instance);

  bestValue = -1;
  takenValue = takenWeight = 0;

  if (upperBound == UB1) {
    maximumRemainingValue = 0;

    for (size_t i = 0; i <= instance->GetItemCnt(); ++i) {
      maximumRemainingValue += instance->GetItemValue(i);
    }
  }

  findSolutions(1);
}

void KnapsackBBSolver::findSolutions(size_t itemNum) {

  // If time has run out, exit early
  if (timeSince(startTime) > maxDuration) {
    return;
  }

  // These are static so that the getters are only invoked once
  size_t static capacity = instance->GetCapacity();
  uint32_t static itemCount = instance->GetItemCnt();

  // If this is a leaf node (all items have been chosen)
  if (itemNum > itemCount) {

    // Update the best value so-far
    int32_t currentValue = currentSolution->ComputeValue();
    bestValue = bestSolution->GetValue();

    if (currentValue > bestValue) {
      bestSolution->Copy(currentSolution);
      bestValue = bestSolution->GetValue();
    }
    return;
  }

  auto itemWeight = instance->GetItemWeight(itemNum);
  auto itemValue = instance->GetItemValue(itemNum);

  if (takenWeight + itemWeight <= capacity) {

    takenWeight += itemWeight;
    takenValue += itemValue;

    currentSolution->TakeItem(itemNum);

    findSolutions(itemNum + 1);

    takenWeight -= itemWeight;
    takenValue -= itemValue;

    currentSolution->DontTakeItem(itemNum);
  }

  switch (upperBound) {
  case UB1:
    // We are chosing not to take this item
    maximumRemainingValue -= itemValue;

    // If we can't do better than the best solution found so far, backtrack
    if (maximumRemainingValue < bestValue) {
      maximumRemainingValue += itemValue;
      return;
    }
    findSolutions(itemNum + 1);

    maximumRemainingValue += itemValue;
    break;
  case UB2:

  {
    uint32_t remainingCapacity = capacity - takenWeight;

    auto remaining = sumRemainingValuesThatFit(itemNum + 1, remainingCapacity);
    if (takenValue + remaining < bestValue) {
      return;
    }
  }

    findSolutions(itemNum + 1);
    break;
  case UB3:
    // TODO: Implement upper bound 3
    currentSolution->DontTakeItem(itemNum);
    findSolutions(itemNum + 1);
    break;
  }
}

int32_t
KnapsackBBSolver::sumRemainingValuesThatFit(size_t itemNum,
                                            uint32_t remainingCapacity) {

  int32_t sum = 0;
  size_t itemCount = instance->GetItemCnt();

  for (size_t i = itemNum; i <= itemCount; ++i) {

    if (instance->GetItemWeight(i) < remainingCapacity) {

      sum += instance->GetItemValue(i);
    }
  }
  return sum;
}
