src = $(wildcard *.cc)

nn: NeuralNetwork.o nn.o
	$(CXX) -std=c++11 -o nn nn.cc NeuralNetwork.cc

.PHONY: clean
clean:
	rm -f $(obj) nn
