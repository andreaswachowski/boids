#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <vector>

struct Boid {
  float x, y;
  float vx, vy;
};

void update_boids(std::vector<Boid>& boids, int max_x, int max_y) {
  for (auto& boid : boids) {
    boid.x += boid.vx;
    boid.y += boid.vy;

    // Wrap around screen edges
    if (boid.x < 0)
      boid.x += max_x;
    if (boid.x >= max_x)
      boid.x -= max_x;
    if (boid.y < 0)
      boid.y += max_y;
    if (boid.y >= max_y)
      boid.y -= max_y;
  }
}

int main() {
  srand(time(0));
  initscr();
  noecho();
  curs_set(FALSE);

  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);

  std::vector<Boid> boids(20);
  for (auto& boid : boids) {
    boid.x = rand() % max_x;
    boid.y = rand() % max_y;
    boid.vx = (rand() % 3 - 1) * 0.5;  // Random velocities
    boid.vy = (rand() % 3 - 1) * 0.5;
  }

  while (true) {
    clear();

    for (const auto& boid : boids) {
      mvprintw(static_cast<int>(boid.y), static_cast<int>(boid.x), "o");
    }

    refresh();
    update_boids(boids, max_x, max_y);
    napms(100);  // Pause for 100ms
  }

  endwin();
  return 0;
}
