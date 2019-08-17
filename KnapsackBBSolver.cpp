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

  auto itemCount = instance->GetItemCnt();

  items.reserve(itemCount);

  for (int i = 0; i < itemCount; ++i) {

    items.emplace_back(Item{i + 1, instance->GetItemWeight(i + 1),
                            instance->GetItemValue(i + 1)});
  }

  if (upperBound == UB1) {
    maximumRemainingValue = 0;

    for (auto item : items) {
      maximumRemainingValue += item.value;
    }
  }

  if (upperBound == UB3) {

    // Fractional knapsack requires items to be sorted by the ratio
    // itemValue / itemWeight
    std::sort(items.begin(), items.end(), [](Item const &a, Item const &b) {
      return a.value / (double)a.weight > b.value / (double)b.weight;
    });
  }

  findSolutions(0);
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
  if (itemNum == itemCount) {

    // Update the best value so-far
    int32_t currentValue = currentSolution->ComputeValue();
    bestValue = bestSolution->GetValue();

    if (currentValue > bestValue) {
      bestSolution->Copy(currentSolution);
      bestValue = bestSolution->GetValue();
    }
    return;
  }

  auto itemWeight = items[itemNum].weight;
  auto itemValue = items[itemNum].value;

  if (takenWeight + itemWeight <= capacity) {

    takenWeight += itemWeight;
    takenValue += itemValue;

    currentSolution->TakeItem(items[itemNum].originalPosition);

    findSolutions(itemNum + 1);

    takenWeight -= itemWeight;
    takenValue -= itemValue;

    currentSolution->DontTakeItem(items[itemNum].originalPosition);
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
  case UB2: {
    uint32_t remainingCapacity = capacity - takenWeight;

    auto remaining = sumRemainingValuesThatFit(itemNum + 1, remainingCapacity);

    if (takenValue + remaining < bestValue) {
      return;
    }

    findSolutions(itemNum + 1);

    break;
  }
  case UB3: {
    uint32_t remainingCapacity = capacity - takenWeight;

    double valueUpperBound =
        takenValue + solveFractionalKnapsack(itemNum, remainingCapacity);

    if (valueUpperBound <= bestValue) {
      return;
    }

    findSolutions(itemNum + 1);

    break;
  }
  }
}

int32_t
KnapsackBBSolver::sumRemainingValuesThatFit(size_t itemNum,
                                            uint32_t remainingCapacity) {

  int32_t sum = 0;

  for (size_t i = itemNum; i < items.size(); ++i) {

    if (items[i].weight < remainingCapacity) {

      sum += items[i].value;
    }
  }

  return sum;
}

double KnapsackBBSolver::solveFractionalKnapsack(size_t itemNum,
                                                 uint32_t capacity) {

  int32_t valueSum = 0, weightSum = 0;
  size_t i;

  for (i = itemNum; i < items.size(); ++i) {

    if (weightSum + items[i].weight > capacity)
      break;

    weightSum += items[i].weight;
    valueSum += items[i].value;
  }

  if (i == items.size()) {

    // Everything fits!
    return valueSum;
  } else {

    // Not every item fits.
    // Compute the value per unit weight of the most valuable remaining item
    double valuePerWeight = (double)items[i].value / items[i].weight;
    // Take as much of the item as will fit in the knapasack
    auto remainingCapacity = capacity - weightSum;
    double fractionalValue = remainingCapacity * valuePerWeight;

    return valueSum + fractionalValue;
  }
}
