#include <time.h>

static unsigned long millis_skew = 0;
static unsigned long micros_skew = 0;

unsigned long millis()
{
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
	return (tp.tv_sec * 1'000 + tp.tv_nsec / 1'000'000) + millis_skew;
}

unsigned long micros()
{
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC_RAW, &tp);
	return (tp.tv_sec * 1'000'000 + tp.tv_nsec / 1'000) + micros_skew;
}

void set_millis_skew(unsigned long skew) { millis_skew = skew; }
void set_micros_skew(unsigned long skew) { micros_skew = skew; }

unsigned long timed_test(void (*cb)())
{
  unsigned long initial_time = micros();
  cb();
  unsigned long final_time = micros();

  return final_time - initial_time;
}
