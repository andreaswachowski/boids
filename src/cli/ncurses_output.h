#pragma once

#include <vector>
#include "boid.h"
#include "output_handler.h"

class NcursesOutput : public OutputHandler {
  public:
  NcursesOutput() = default;
  void initialize(int& max_x, int& max_y) override;

  void render(const std::vector<Boid>& boids) override;

  void cleanup() override;
};
