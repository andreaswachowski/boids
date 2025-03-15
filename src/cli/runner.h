#pragma once

#include <string>
#include <vector>
#include "output_handler.h"

namespace CLI {
class App;
}

class Boid;

struct SimulationConfig {
  unsigned int seed;
  unsigned int num_iterations;
  unsigned int num_boids;
  std::string logfile;
  unsigned int delay_ms;
};

class Runner {
  public:
  explicit Runner(OutputHandler& output_handler);

  ~Runner() = default;

  // Avoid copying and moving since we use a reference data member.
  Runner(const Runner&) = delete;
  Runner& operator=(const Runner&) = delete;
  Runner(Runner&&) = delete;
  Runner& operator=(Runner&&) = delete;

  // NOLINTBEGIN(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays, modernize-avoid-c-arrays)
  int run(int argc, char* argv[]);
  // NOLINTEND(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays, modernize-avoid-c-arrays)

  private:
  static SimulationConfig configure_cli_args(CLI::App& app);
  static void update_boids(std::vector<Boid>& boids);
  OutputHandler& output_;
};
