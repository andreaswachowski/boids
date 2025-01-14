#include <ncurses.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <vector>
#include "boid.h"

void update_boid_chunk(std::vector<Boid>& boids, size_t start, size_t end) {
  for (size_t i = start; i < end; ++i) {
    boids[i].update();
  }
}

void update_boids(std::vector<Boid>& boids, int num_threads) {
  size_t total = boids.size();
  size_t chunk_size = std::ceil(static_cast<float>(total) / num_threads);

  std::vector<std::thread> threads;

  for (int i = 0; i < num_threads; ++i) {
    size_t start = i * chunk_size;
    size_t end = std::min(start + chunk_size, total);

    if (start < total) {  // Avoid launching empty threads
      threads.emplace_back(update_boid_chunk, std::ref(boids), start, end);
    }
  }

  for (auto& thread : threads) {
    thread.join();
  }
}

int main() {
  srand(time(0));
  initscr();
  noecho();
  curs_set(FALSE);

  const int num_threads = std::thread::hardware_concurrency();

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
    update_boids(boids, num_threads);
    napms(100);  // Pause for 100ms
  }

  endwin();
  return 0;
}
