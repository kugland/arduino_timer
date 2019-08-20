docs:
	doxygen ./Doxyfile

test: .PHONY
	$(MAKE) -C test

clean:
	-rm -r html
	$(MAKE) -C test clean

.PHONY:
