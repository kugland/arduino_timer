#include <cstdlib>
#include <cmath>
#include <cstdint>

#include "linux_test_funcs.hpp"
#include "../src/arduino_timer.hpp"

auto callback_250ms = []() {
  timer::one_shot<micros> test;
  test.start(250'000);
  test.wait();
};

void stop_on_max_error(unsigned long expected, unsigned long max_error, unsigned long actual)
{
  if (std::abs(static_cast<long long>(actual - expected)) > max_error) {
    std::exit(1);
  }
}

int main(int argc, char const *argv[])
{
  for (int i = 0; i < 8; i++) {
    stop_on_max_error(250'000, 1'000, timed_test(callback_250ms));
  }
  return 0;
}
