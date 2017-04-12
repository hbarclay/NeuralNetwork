
.PHONY: clean nn

nn:
	$(CXX) -std=c++11 src/StatsFile.cc src/NeuralNetwork.cc src/Evolution.cc src/Evaluation.cc src/nn.cc -o nn OpenBLAS-build/lib/libopenblas.a -I OpenBLAS-build/include/ -lpthread -Iinclude/

