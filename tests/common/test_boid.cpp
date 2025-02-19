#include <gtest/gtest.h>
#include <random>
#include "boid.h"

class BoidTest : public testing::Test {
  protected:
  BoidTest()
      : gen_(dev()),
        boid_(gen_, max_x, max_y) {};

  constexpr static unsigned int max_x = 100;
  constexpr static unsigned int max_y = 200;

  std::random_device dev;
  std::mt19937 gen_;
  Boid boid_;
};

TEST_F(BoidTest, InitializesCorrectly) {
  EXPECT_EQ(boid_.max_x, max_x);
  EXPECT_EQ(boid_.max_y, max_y);
}

TEST_F(BoidTest, UpdatesCorrectly) {
  const double x{boid_.x};
  const double y{boid_.y};
  const double vx{boid_.vx};
  const double vy{boid_.vy};

  boid_.update();

  EXPECT_EQ(boid_.x, x + vx);
  EXPECT_EQ(boid_.y, y + vy);
}
