#include <gtest/gtest.h>
#include "../src/boid.h"

TEST(Boid, Constructor) {
  Boid b(100, 200);
  EXPECT_EQ(b.max_x, 100);
  EXPECT_EQ(b.max_y, 200);
}

TEST(Boid, Update) {
  Boid b(100, 200);
  float x{b.x};
  float y{b.y};
  float vx{b.vx};
  float vy{b.vy};

  b.update();

  EXPECT_EQ(b.x, x + vx);
  EXPECT_EQ(b.y, y + vy);
}
