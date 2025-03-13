#pragma once

#include <string>
#include <vector>

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
  // NOLINTBEGIN(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays, modernize-avoid-c-arrays)
  static int run(int argc, char* argv[]);
  // NOLINTEND(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays, modernize-avoid-c-arrays)

  private:
  static SimulationConfig configure_cli_args(CLI::App& app);
  static void update_boids(std::vector<Boid>& boids);
};
