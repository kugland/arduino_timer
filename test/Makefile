ALL_TESTS_SRC   := $(wildcard ??-*.cpp)
ALL_TESTS_BIN   := $(patsubst %.cpp,%.bin,$(ALL_TESTS_SRC))

CXXFLAGS        := -g -O0

test: $(ALL_TESTS_BIN)
	@for t in $(ALL_TESTS_BIN); do \
		printf "Running test ./$${t} ... " ; \
		./"$$t" && echo "PASSED" || echo "ERROR"; \
	done

clean:
	-rm $(ALL_TESTS_BIN)

%.bin: %.cpp linux_test_funcs.cpp ../src/arduino_timer.hpp
	$(CXX) $(CXXFLAGS) -o $@ $< linux_test_funcs.cpp -Wno-narrowing
