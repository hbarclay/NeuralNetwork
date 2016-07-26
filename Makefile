src = $(wildcard *.cc)
obj = $(src:.cc=.o)


nn: $(obj)
	$(CXX) -o $@ $^

.PHONY: clean
clean:
	rm -f $(obj) nn
