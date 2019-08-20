#include <cstdlib>
#include <cstdint>

#include "linux_test_funcs.hpp"
#include "../src/arduino_timer.hpp"

timer::one_shot<millis, std::uint8_t> test{200, []() { std::exit(0); }};
timer::one_shot<millis> watchdog{2000, []() { std::exit(1); }};

int main(int argc, char const *argv[])
{
  timer::wait(test, watchdog);
  return 0;
}
