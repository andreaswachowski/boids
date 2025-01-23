#pragma once

#include <random>

struct Boid {
  int max_x;
  int max_y;

  double x, y;
  double vx, vy;

  Boid(std::mt19937& gen, int max_x_, int max_y_);

  void update();
};
