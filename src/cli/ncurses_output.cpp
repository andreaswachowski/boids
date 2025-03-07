#include <vector>
#include <ncurses.h>
#include "boid.h"
#include "ncurses_output.h"

void NcursesOutput::initialize(int& max_x, int& max_y) {
  initscr();
  noecho();
  curs_set(FALSE);
  getmaxyx(stdscr, max_y, max_x);
};

void NcursesOutput::render(const std::vector<Boid>& boids) {
  {
    clear();
    for (const auto& boid : boids) {
      // NOLINTNEXTLINE(cppcoreguidelines-pro-type-vararg, hicpp-vararg)
      mvprintw(static_cast<int>(boid.y), static_cast<int>(boid.x), "o");
    }
    refresh();
  }
}

void NcursesOutput::cleanup() {
  endwin();
}
