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

class KnapsackBBSolver {
private:
  struct Item {
    /// Specifies the position of this item in the original item list of the
    /// KnapsackInstance.
    int originalPosition;
    int weight, value;
  };

  class FractionalKnapsack {

    std::vector<Item> const &items;
    int32_t valueSum, weightSum, fractionalValue, fractionalWeight, capacity;
    size_t fractionalItemNum;

    void computeStartingFrom(size_t startingPoint);

  public:
    FractionalKnapsack(std::vector<Item> const &items, uint32_t capacity);
    void untake(size_t itemNum);
    int32_t getSolution() { return valueSum + fractionalValue; }
  };

  UPPER_BOUND const upperBound;
  KnapsackInstance *instance = nullptr;
  KnapsackSolution *currentSolution = nullptr;
  KnapsackSolution *bestSolution = nullptr;
  std::chrono::high_resolution_clock::time_point startTime;
  std::chrono::duration<double> maxDuration = std::chrono::seconds(10);
  int32_t bestValue = 0, takenWeight = 0, takenValue = 0, itemCount = 0;
  std::vector<Item> items;
  uint32_t capacity = 0;

  // Used for upper bound 1
  int32_t maximumRemainingValue = 0;

  int32_t sumRemainingValuesThatFit(size_t itemNum, uint32_t capacity);

  void findSolutions(size_t itemNum, FractionalKnapsack fractionalKnapsack);

public:
  explicit KnapsackBBSolver(UPPER_BOUND const upperBound)
      : upperBound(upperBound) {}

  ~KnapsackBBSolver() = default;

  void Solve(KnapsackInstance *instance, KnapsackSolution *solution);
};

#endif // KNAPSACKBBSOLVER_H
