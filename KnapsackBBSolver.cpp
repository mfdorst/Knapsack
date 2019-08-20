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
#include <cmath>

void KnapsackBBSolver::Solve(KnapsackInstance *instance_,
                             KnapsackSolution *solution_) {

  startTime = getTime();

  instance = instance_;
  bestSolution = solution_;
  currentSolution = new KnapsackSolution(instance);

  bestValue = -1;
  takenValue = takenWeight = 0;

  itemCount = instance->GetItemCnt();
  capacity = instance->GetCapacity();

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

  // The initial fractional knapsack is computed upon construction
  findSolutions(0, FractionalKnapsack(items, capacity));
}

void KnapsackBBSolver::findSolutions(size_t itemNum,
                                     FractionalKnapsack fractionalKnapsack) {

  // If time has run out, exit early
  if (timeSince(startTime) > maxDuration) {
    return;
  }

  // These are static so that the getters are only invoked once
  capacity = instance->GetCapacity();
  itemCount = instance->GetItemCnt();

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

    findSolutions(itemNum + 1, fractionalKnapsack);

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
    findSolutions(itemNum + 1, fractionalKnapsack);

    maximumRemainingValue += itemValue;
    break;
  case UB2: {
    uint32_t remainingCapacity = capacity - takenWeight;

    auto remaining = sumRemainingValuesThatFit(itemNum + 1, remainingCapacity);

    if (takenValue + remaining < bestValue) {
      return;
    }

    findSolutions(itemNum + 1, fractionalKnapsack);

    break;
  }
  case UB3: {
    uint32_t remainingCapacity = capacity - takenWeight;

    fractionalKnapsack.untake(itemNum);

    double valueUpperBound = fractionalKnapsack.getSolution();

    if (valueUpperBound <= bestValue) {
      return;
    }

    findSolutions(itemNum + 1, fractionalKnapsack);

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

KnapsackBBSolver::FractionalKnapsack::FractionalKnapsack(
    const std::vector<Item> &items, uint32_t capacity)
    : items(items), capacity(capacity) {

  valueSum = weightSum = fractionalValue = fractionalWeight = 0;

  fractionalItemNum = items.size();

  computeStartingFrom(0);
}

void KnapsackBBSolver::FractionalKnapsack::untake(size_t itemNum) {

  // If the item being untaken is not in the fractional knapsack, do nothing.
  if (itemNum > fractionalItemNum) {
    return;
  }

  if (itemNum < fractionalItemNum) {

    weightSum -= items[itemNum].weight;
    valueSum -= items[itemNum].value;

    computeStartingFrom(fractionalItemNum);
  }
  if (itemNum == fractionalItemNum) {

    computeStartingFrom(fractionalItemNum + 1);
  }
}

void KnapsackBBSolver::FractionalKnapsack::computeStartingFrom(
    size_t startingPoint) {

  if (startingPoint >= items.size()) {
    fractionalWeight = 0;
    fractionalValue = 0;
    return;
  }

  if (fractionalItemNum < startingPoint) {
    fractionalItemNum = startingPoint;
  }

  Item item{};

  // Add up as many items as will fit entirely
  for (size_t i = startingPoint; i < items.size(); ++i) {

    item = items[i];

    if (weightSum + item.weight > capacity) {

      fractionalItemNum = i;
      break;
    }

    weightSum += item.weight;
    valueSum += item.value;
  }

  // If all items fit (there is no fractional item)
  if (fractionalItemNum == items.size()) {

    fractionalWeight = 0;
    fractionalValue = 0;

  } else {

    // Not every items fits. Compute the fractional value.
    double valuePerWeight = (double)item.value / item.weight;
    fractionalWeight = capacity - weightSum;
    fractionalValue = std::floor(fractionalWeight * valuePerWeight);
  }
}
