#include <gtest/gtest.h>
#include <random>
#include "boid.h"

constexpr unsigned int rand_seed = 1;
constexpr unsigned int max_x = 100;
constexpr unsigned int max_y = 200;

TEST(Boid, Constructor) {
  std::mt19937 gen(rand_seed);  // NOLINT(cert-msc32-c,cert-msc51-cpp)
  const Boid boid(gen, max_x, max_y);
  EXPECT_EQ(boid.max_x, max_x);
  EXPECT_EQ(boid.max_y, max_y);
}

TEST(Boid, Update) {
  std::mt19937 gen(rand_seed);  // NOLINT(cert-msc32-c,cert-msc51-cpp)
  Boid boid(gen, max_x, max_y);
  const double x{boid.x};
  const double y{boid.y};
  const double vx{boid.vx};
  const double vy{boid.vy};

  boid.update();

  EXPECT_EQ(boid.x, x + vx);
  EXPECT_EQ(boid.y, y + vy);
}
