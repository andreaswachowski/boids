#pragma once

#include <vector>
#include "boid.h"

class OutputHandler {
  public:
  OutputHandler() = default;
  OutputHandler(const OutputHandler&) = default;
  OutputHandler& operator=(OutputHandler const&) = default;
  OutputHandler(OutputHandler&&) = default;
  OutputHandler& operator=(OutputHandler&&) = default;
  virtual ~OutputHandler() = default;
  virtual void initialize(int& max_x, int& max_y) = 0;
  virtual void render(const std::vector<Boid>& boids) = 0;
  virtual void cleanup() = 0;
};
