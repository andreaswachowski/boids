#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "boid.h"

void update_boids(std::vector<Boid>& boids) {
  for (auto& boid : boids) {
    boid.update();
  }
}

int main() {
  srand(time(0));
  initscr();
  noecho();
  curs_set(FALSE);

  const int num_boids = 20;

  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);

  std::vector<Boid> boids;
  boids.reserve(num_boids);
  for (int i = 0; i < num_boids; ++i) {
    boids.emplace_back(max_x, max_y);
  }

  while (true) {
    clear();

    for (const auto& boid : boids) {
      mvprintw(static_cast<int>(boid.y), static_cast<int>(boid.x), "o");
    }

    refresh();
    update_boids(boids);
    napms(100);  // Pause for 100ms
  }

  endwin();
  return 0;
}
