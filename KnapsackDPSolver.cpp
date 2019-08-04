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

/// Get the maximum of two numbers
/// \returns whichever number is greater
uint32_t max(uint32_t a, uint32_t b);

void KnapsackDPSolver::Solve(KnapsackInstance *instance_,
                             KnapsackSolution *solution_) {

  instance = instance_;
  solution = solution_;

  size_t itemCount = instance->GetItemCnt();
  size_t capacity = instance->GetCapacity();

  // A 2-D array of dimensions ItemCount+1 x Capacity+1.
  // Each cell stores the value of the optimal solution for the capacity and
  // item count indicated by its row and column.
  // For example, `solutionTable[n][m]` will store the value of the optimal
  // solution for a 0/1 knapsack problem with capacity n and item count m.
  // The n items considered will be the first n items as they are ordered in
  // the KnapsackInstance.
  // Initially, all cells are 0.
  std::vector<std::vector<uint32_t>> solutionTable(
      itemCount + 1, std::vector<uint32_t>(capacity + 1));

  // Build the table of all optimal solutions...
  // The first row will always stay all 0's, (no items), so we can skip it.
  for (size_t i = 1; i <= itemCount; ++i) {

    size_t itemWeight = instance->GetItemWeight(i);
    uint32_t itemValue = instance->GetItemValue(i);

    for (size_t c = 0; c <= capacity; ++c) {

      // i: item number, c: capacity

      if (c < itemWeight) {

        // Cannot take the item - solution is the same as the row above.
        solutionTable[i][c] = solutionTable[i - 1][c];

      } else {

        // Calculate remaining capacity and value if this item is taken
        size_t remainingCapacity = c - itemWeight;

        uint32_t remainingValue = solutionTable[i - 1][remainingCapacity];

        uint32_t valueIfTaken = itemValue + remainingValue;

        // If not taken, the value will be the same as the row above.
        uint32_t valueIfNotTaken = solutionTable[i - 1][c];

        // Take whichever value is greater
        solutionTable[i][c] = max(valueIfTaken, valueIfNotTaken);
      }
    }
  }
  // The table of all optimal solutions is built.
  // The value at solutionTable[itemCount][capacity] is the optimal value for
  // this knapsack problem.

  // Now we need to find the items used to get that value.
  // Each row in the table corresponds to an item. If the value in a cell is
  // greater than the value in the cell above it, that indicates that the item
  // was taken.

  // Start at the ultimate solution
  size_t c = capacity;

  for (size_t i = itemCount; i > 0; --i) {

    // Is the value of the current cell higher than that of the previous cell?
    if (solutionTable[i][c] > solutionTable[i - 1][c]) {

      // Then the item was taken.
      solution->TakeItem(i);

      // Jump backwards to the cell where the item was taken
      c -= instance->GetItemWeight(i);
    }
  }

  solution->ComputeValue();
}

uint32_t max(uint32_t a, uint32_t b) { return a > b ? a : b; }
