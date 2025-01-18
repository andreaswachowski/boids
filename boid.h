#pragma once

struct Boid {
  const int max_x, max_y;
  float x, y;
  float vx, vy;

  Boid(int max_x_, int max_y_);

  void update();
};
