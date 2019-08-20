docs:
	doxygen ./Doxyfile

clean:
	-rm -r html
	$(MAKE) -C test clean
