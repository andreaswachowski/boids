#include "boid.h"

#include <cstdlib>

Boid::Boid(int max_x_, int max_y_)
    : max_x(max_x_),
      max_y(max_y_),
      x(rand() % max_x),
      y(rand() % max_y),
      vx((rand() % 3 - 1) * 0.5),
      vy((rand() % 3 - 1) * 0.5) {};

void Boid::update() {
  x += vx;
  y += vy;

  // Wrap around screen edges
  if (x < 0)
    x += max_x;
  if (x >= max_x)
    x -= max_x;
  if (y < 0)
    y += max_y;
  if (y >= max_y)
    y -= max_y;
};
