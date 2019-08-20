#ifndef LINUX_TEST_FUNCS_H_15F79B84F6D53D3FCF0A08F232523CF7054D6B2E
#define LINUX_TEST_FUNCS_H_15F79B84F6D53D3FCF0A08F232523CF7054D6B2E

unsigned long millis();
unsigned long micros();
void set_millis_skew(unsigned long skew);
void set_micros_skew(unsigned long skew);
unsigned long timed_test(void (*cb)());

#endif /* LINUX_TEST_FUNCS_H_15F79B84F6D53D3FCF0A08F232523CF7054D6B2E */
