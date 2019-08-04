//===-- Time.h - Helper functions for time tracking -------------*- C++ -*-===//
//
// Author: Michael Dorst
//
//===----------------------------------------------------------------------===//
/// \file
/// This file contains functions that simplify the syntax of time tracking
//===----------------------------------------------------------------------===//

#ifndef KNAPSACK_TIME_H
#define KNAPSACK_TIME_H

#include <chrono>

/// Get the current time
std::chrono::high_resolution_clock::time_point getTime() {
  return std::chrono::high_resolution_clock::now();
}

/// Get the duration between a previous time and now
/// \param previousTime The previous time
std::chrono::duration<double>
timeSince(std::chrono::high_resolution_clock::time_point previousTime) {

  auto currentTime = std::chrono::high_resolution_clock::now();

  return currentTime - previousTime;
}

#endif // KNAPSACK_TIME_H
