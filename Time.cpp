//===-- Time.h - Helper functions for time tracking -----------------------===//
//
// Author: Michael Dorst
//
//===----------------------------------------------------------------------===//
/// \file
/// This file contains functions that simplify the syntax of time tracking
//===----------------------------------------------------------------------===//

#include "Time.h"

std::chrono::high_resolution_clock::time_point getTime() {
  return std::chrono::high_resolution_clock::now();
}

std::chrono::duration<double>
timeSince(std::chrono::high_resolution_clock::time_point previousTime) {

  auto currentTime = std::chrono::high_resolution_clock::now();

  return currentTime - previousTime;
}