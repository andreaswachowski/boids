#include <vector>
#include <string>
#include <gsl/narrow>

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "output_handler.h"
#include "runner.h"

namespace {
using ::testing::_;
}  // namespace

// ArgvHolder seems needlessly complicated, but I did not
// find another way. The test shall be able to declare the
// command line arguments as a plain vector of string literals.
// But the run method requires an array of non-const char pointers -
// that is not purely theoretical either because we may modify them
// with  "argv = app.ensure_utf8(argv);"
//
// Hence the ArgvHolder receives said vector of string literals and
// creates a copy in "storage", with a vector of char pointers "argv"
// to be passed to run.
// storage is a vector of vector of chars and deallocated normally
// when the struct goes out of scope. The pointers are destroyed
// at the same time (without double deallocation because there's no
// delete on the pointers), so all is well.
struct ArgvHolder {
  std::vector<std::vector<char>> storage;
  std::vector<char*> argv;

  explicit ArgvHolder(const std::vector<std::string>& args) {
    storage.reserve(args.size());
    argv.reserve(args.size() + 1);  // +1 for null termination

    for (const auto& arg : args) {
      storage.emplace_back(arg.begin(), arg.end());
      storage.back().push_back('\0');
      argv.push_back(storage.back().data());
    }
    argv.push_back(nullptr);
  }
};

class MockOutputHandler : public OutputHandler {
  public:
  MOCK_METHOD(void, initialize, (int& max_x, int& max_y), (override));
  MOCK_METHOD(void, render, (const std::vector<Boid>& boids), (override));
  MOCK_METHOD(void, cleanup, (), (override));
};

class RunnerTest : public testing::Test {
  protected:
  MockOutputHandler mock_output_;
};

TEST_F(RunnerTest, CanConfigureNumberOfBoids) {
  ArgvHolder argv_holder({"boids", "-s", "0", "-d", "0", "-i", "2"});

  EXPECT_CALL(mock_output_, render(_)).Times(2);

  Runner runner(mock_output_);
  runner.run(gsl::narrow<int>(argv_holder.argv.size() - 1), argv_holder.argv.data());
}
