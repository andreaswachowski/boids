#include "boid.h"

#include <cstdlib>
#include <random>

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters
Boid::Boid(std::mt19937& gen, int max_x_, int max_y_)
    : max_x(max_x_),
      max_y(max_y_),
      x(std::uniform_real_distribution<double>(1.0, max_x_)(gen)),
      y(std::uniform_real_distribution<double>(1.0, max_y_)(gen)),
      vx(std::uniform_int_distribution<int>(-1, 1)(gen) * velocity_scale),
      vy(std::uniform_int_distribution<int>(-1, 1)(gen) * velocity_scale) {};

// NOLINTNEXTLINE(bugprone-easily-swappable-parameters
Boid::Boid(double x_, double y_, double vx_, double vy_, int max_x_, int max_y_)
    : max_x(max_x_),
      max_y(max_y_),
      x(x_),
      y(y_),
      vx(vx_),
      vy(vy_) {};

void Boid::update() {
  x += vx;
  y += vy;

  // Wrap around screen edges
  if (x < 0) {
    x += max_x;
  }
  if (x >= max_x) {
    x -= max_x;
  }
  if (y < 0) {
    y += max_y;
  }
  if (y >= max_y) {
    y -= max_y;
  }
};
