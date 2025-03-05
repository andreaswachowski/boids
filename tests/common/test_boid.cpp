#include <gtest/gtest.h>
#include <random>
#include "boid.h"

class BoidTest : public testing::Test {
  protected:
  BoidTest()
      : gen_(dev()),
        boid_(x, y, vx, vy, max_x, max_y),
        random_boid_(gen_, max_x, max_y) {};

  constexpr static double x = 1.0;
  constexpr static double y = 2.5;
  constexpr static double vx = 3.0;
  constexpr static double vy = 4.5;
  constexpr static unsigned int max_x = 100;
  constexpr static unsigned int max_y = 200;

  std::random_device dev;
  std::mt19937 gen_;
  Boid boid_;
  Boid random_boid_;
};

TEST_F(BoidTest, InitializesRandomlyCorrectly) {
  EXPECT_LE(random_boid_.x, max_x);
  EXPECT_GE(random_boid_.x, 1.0);
  EXPECT_LE(random_boid_.y, max_y);
  EXPECT_GE(random_boid_.y, 1.00);
  EXPECT_LE(random_boid_.vx, Boid::velocity_scale);
  EXPECT_GE(random_boid_.vx, -Boid::velocity_scale);
  EXPECT_LE(random_boid_.vy, Boid::velocity_scale);
  EXPECT_GE(random_boid_.vy, -Boid::velocity_scale);
  EXPECT_EQ(random_boid_.max_x, max_x);
  EXPECT_EQ(random_boid_.max_y, max_y);
}

TEST_F(BoidTest, InitializesCorrectly) {
  EXPECT_EQ(boid_.x, x);
  EXPECT_EQ(boid_.y, y);
  EXPECT_EQ(boid_.vx, vx);
  EXPECT_EQ(boid_.vy, vy);
  EXPECT_EQ(boid_.max_x, max_x);
  EXPECT_EQ(boid_.max_y, max_y);
}

TEST_F(BoidTest, UpdatesCorrectly) {
  boid_.update();

  EXPECT_EQ(boid_.x, x + vx);
  EXPECT_EQ(boid_.y, y + vy);

  // x, y >= max after adding velocity
  const double x_ = max_x;
  const double y_ = max_y;
  Boid boid2(x_, y_, vx, vy, max_x, max_y);
  boid2.update();
  EXPECT_EQ(boid2.x, vx);  // max_x + vx - max_x
  EXPECT_EQ(boid2.y, vy);  // max_y + vy - max_y

  // x, y < 0 after adding (negative) velocity
  const double vx_ = -vx;
  const double vy_ = -vy;
  Boid boid3(0, 0, vx_, vy_, max_x, max_y);
  boid3.update();
  EXPECT_EQ(boid3.x, vx_ + max_x);  // 0 - vx + max_x
  EXPECT_EQ(boid3.y, vy_ + max_y);  // 0 - vy + max_y
}
