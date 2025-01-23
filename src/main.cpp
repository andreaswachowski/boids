#include <ncurses.h>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <thread>
#include <vector>

#include <CLI/CLI.hpp>
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

constexpr unsigned int DEFAULT_NUM_BOIDS = 20;
constexpr unsigned int DEFAULT_DELAY_MS = 100;

int main(int argc, char* argv[]) {
  // -- Command line arguments --------------------------------------------
  CLI::App app{"Boids"};
  argv = app.ensure_utf8(argv);

  unsigned int seed = INT_MAX;
  unsigned int num_boids = DEFAULT_NUM_BOIDS;
  std::string logfile = "boids.log";
  unsigned int delay_ms = DEFAULT_DELAY_MS;
  app.add_option("-s,--seed", seed, "Random seed (default random)");
  app.add_option("-b,--boids", num_boids, "Number of boids (default 20)");
  app.add_option("-d,--delay", delay_ms,
                 "Delay between iterations (in ms, default 100)");
  app.add_option("-o,--logfile", logfile,
                 "Logfile (default \"boids.log\". The file is placed in the "
                 "directory \"logs\". It is not possible to log to stdout.)");
  app.set_config("-c,--config", "boids.toml", "Read a config file", false);

  CLI11_PARSE(app, argc, argv);

  std::cout << app.config_to_str(true, true);

  // -- Logger initialization ---------------------------------------------
  spdlog::cfg::load_env_levels();

  try {
    auto logger = spdlog::basic_logger_mt("basic_logger", "logs/" + logfile);
    spdlog::set_default_logger(logger);
  } catch (const spdlog::spdlog_ex& ex) {
    std::cout << "Log init failed: " << ex.what() << '\n';
    return 1;
  }

  // -- ncursses setup ----------------------------------------------------
  initscr();
  noecho();
  curs_set(FALSE);

  // -- simulation setup --------------------------------------------------
  const unsigned int num_threads = std::thread::hardware_concurrency();

  int max_x = 0;
  int max_y = 0;
  getmaxyx(stdscr, max_y, max_x);

  if (seed == INT_MAX) {
    std::random_device rand_device;
    seed = rand_device();
  }
  spdlog::info("Using random seed {}.", seed);

  std::mt19937 gen(seed);
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
    std::this_thread::sleep_for(std::chrono::milliseconds(delay_ms));
  }

  endwin();
  return 0;
}
