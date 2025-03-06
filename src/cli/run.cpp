#include "run.h"

#include <ncurses.h>
#include <algorithm>
#include <chrono>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <execution>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include <CLI/CLI.hpp>
#include "boid.h"
#include "spdlog/cfg/env.h"
#include "spdlog/common.h"
#include "spdlog/logger.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

constexpr unsigned int DEFAULT_NUM_BOIDS = 20;
constexpr unsigned int DEFAULT_DELAY_MS = 100;

struct SimulationConfig {
  unsigned int seed = INT_MAX;
  unsigned int num_boids = DEFAULT_NUM_BOIDS;
  std::string logfile = "boids.log";
  unsigned int delay_ms = DEFAULT_DELAY_MS;
};

namespace {
void update_boids(std::vector<Boid>& boids) {
  std::for_each(std::execution::par, boids.begin(), boids.end(), [](Boid& boid) { boid.update(); });
}

SimulationConfig configure_cli_args(CLI::App& app) {
  SimulationConfig config;
  app.add_option("-s,--seed", config.seed, "Random seed (default random)");
  app.add_option("-b,--boids", config.num_boids, "Number of boids (default 20)");
  app.add_option("-d,--delay", config.delay_ms, "Delay between iterations (in ms, default 100)");
  app.add_option("-o,--logfile", config.logfile,
                 R"(Logfile (default "boids.log"). The file is placed in the "logs" directory.)");
  app.set_config("-c,--config", "boids.toml", "Read a config file", false);

  if (config.seed == INT_MAX) {
    std::random_device rand_device;
    config.seed = rand_device();
  }

  return config;
}
}  // namespace

// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays, modernize-avoid-c-arrays)
int run(int argc, char* argv[]) {
  CLI::App app{"Boids"};

  auto config = configure_cli_args(app);
  argv = app.ensure_utf8(argv);

  CLI11_PARSE(app, argc, argv);

  // -- Logger initialization ---------------------------------------------
  spdlog::cfg::load_env_levels();

  std::shared_ptr<spdlog::logger> logger;

  try {
    logger = spdlog::basic_logger_mt("basic_logger", "logs/" + config.logfile);
    spdlog::set_default_logger(logger);
  } catch (const spdlog::spdlog_ex& ex) {
    std::cerr << "Log init failed: " << ex.what() << '\n';
    return 1;
  }

  // -- ncurses setup -----------------------------------------------------
  initscr();
  noecho();
  curs_set(FALSE);

  // -- simulation setup --------------------------------------------------
  int max_x = 0;
  int max_y = 0;
  getmaxyx(stdscr, max_y, max_x);

  spdlog::info("Using random seed {}.", config.seed);
  logger->flush();  // ensure that the seed is logged.

  std::mt19937 gen(config.seed);

  std::vector<Boid> boids;
  boids.reserve(config.num_boids);
  for (int i = 0; i < config.num_boids; ++i) {
    boids.emplace_back(gen, max_x, max_y);
  }

  while (true) {
    clear();

    for (const auto& boid : boids) {
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg, hicpp-vararg)
      mvprintw(static_cast<int>(boid.y), static_cast<int>(boid.x), "o");
    }

    refresh();
    update_boids(boids);
    std::this_thread::sleep_for(std::chrono::milliseconds(config.delay_ms));
  }

  endwin();
  return 0;
}
