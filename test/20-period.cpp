#include "linux_test_funcs.hpp"
#include "../src/arduino_timer.hpp"

int a = 1, b = 1, c = 1, d = 1, e = 1, f = 1;

timer::periodic<micros> timer_a{100'000, []() { ++a; }};
timer::periodic<micros> timer_b{200'000, []() { ++b; }};
timer::periodic<micros> timer_c{300'000, []() { ++c; }};
timer::periodic<micros> timer_d{400'000, []() { ++d; }};
timer::periodic<micros> timer_e{500'000, []() { ++e; }};
timer::periodic<micros> timer_f{600'000, []() { ++f; }};
timer::one_shot<micros> watchdog{6'000'000, []() {
  timer_a.stop();
  timer_b.stop();
  timer_c.stop();
  timer_d.stop();
  timer_e.stop();
  timer_f.stop();
}};

int main(int argc, char const *argv[])
{
  timer::wait(timer_a, timer_b, timer_c, timer_d, timer_e, timer_f, watchdog);
  return (a == 60 && b == 30 && c == 20 && d == 15 && e == 12 && f == 10) ? 0 : 1;
}
