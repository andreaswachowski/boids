#include <ncurses.h>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include "boid.h"
#include "spdlog/cfg/env.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

namespace {
void update_boid_chunk(std::vector<Boid>& boids, size_t start, size_t end) {
  for (size_t i = start; i < end; ++i) {
    boids[i].update();
  }
}

void update_boids(std::vector<Boid>& boids, unsigned int num_threads) {
  size_t total = boids.size();
  auto chunk_size = static_cast<size_t>(
      std::ceil(static_cast<float>(total) / static_cast<float>(num_threads)));

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
}  // namespace

constexpr unsigned int rand_seed = 1;

int main(int /*argc*/, char* /*argv*/[]) {
  initscr();
  noecho();
  curs_set(FALSE);

  spdlog::cfg::load_env_levels();

  try {
    auto logger =
        spdlog::basic_logger_mt("basic_logger", "logs/development.txt");
    spdlog::set_default_logger(logger);
  } catch (const spdlog::spdlog_ex& ex) {
    std::cout << "Log init failed: " << ex.what() << '\n';
    return 1;
  }

  const unsigned int num_threads = std::thread::hardware_concurrency();

  const int num_boids = 20;
  const int pause_ms = 100;

  int max_x = 0;
  int max_y = 0;
  getmaxyx(stdscr, max_y, max_x);

  // For now, use predictable random sequence to aid debugging
  std::mt19937 gen(rand_seed);  // NOLINT(cert-msc32-c,cert-msc51-cpp)
  std::uniform_int_distribution<int> rand_x_gen(1, max_x);
  std::uniform_int_distribution<int> rand_y_gen(1, max_y);

  float x = std::uniform_real_distribution<float>(
      1.0, static_cast<float>(max_x))(gen);

  std::vector<Boid> boids;
  boids.reserve(num_boids);
  for (int i = 0; i < num_boids; ++i) {
    boids.emplace_back(gen, max_x, max_y);
  }

  while (true) {
    clear();

    for (const auto& boid : boids) {
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg, hicpp-vararg)
      mvprintw(static_cast<int>(boid.y), static_cast<int>(boid.x), "o");
    }

    refresh();
    update_boids(boids, num_threads);
    napms(pause_ms);
  }

  endwin();
  return 0;
}
