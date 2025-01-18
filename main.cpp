#include <ncurses.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>
#include <vector>

#include "boid.h"
#include "spdlog/cfg/env.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

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
      spdlog::debug("Thread {}: Boids {} to {}", i, i * chunk_size,
                    (i * chunk_size) + chunk_size);
      threads.emplace_back(update_boid_chunk, std::ref(boids), start, end);
    }
  }

  for (auto& thread : threads) {
    thread.join();
  }
}

int main(int argc, char* argv[]) {
  srand(time(0));
  initscr();
  noecho();
  curs_set(FALSE);

  spdlog::cfg::load_env_levels();

  try {
    auto logger =
        spdlog::basic_logger_mt("basic_logger", "logs/development.txt");
    spdlog::set_default_logger(logger);
  } catch (const spdlog::spdlog_ex& ex) {
    std::cout << "Log init failed: " << ex.what() << std::endl;
    exit(1);
  }

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
