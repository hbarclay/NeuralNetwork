
.PHONY: clean nn

nn:
	$(CXX) -std=c++11 NeuralNetwork.cc Evolution.cc Evaluation.cc nn.cc -o nn

