#include "runner.h"

#include "ncurses_output.h"

int main(int argc, char* argv[]) {
  NcursesOutput output;
  Runner runner(output);
  return runner.run(argc, argv);
}
