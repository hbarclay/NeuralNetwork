CFLAGS = -std=c++11


nn: NeuralNetwork.o nn.o
	g++ $(CFLAGS) -o nn nn.cc NeuralNetwork.cc Evolution.cc Evaluation.cc 

.PHONY: clean
clean:
	rm -f $(obj) nn
