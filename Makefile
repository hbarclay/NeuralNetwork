
.PHONY: clean nn

nn:
	$(CXX) -std=c++11 src/StatsFile.cc src/NeuralNetwork.cc src/Evolution.cc src/Evaluation.cc src/nn.cc -o nn OpenBLAS/lib/libopenblas.a -I OpenBLAS/include/ -lpthread -Iinclude/

