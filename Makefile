
.PHONY: clean nn

nn:
	$(CXX) -std=c++11 src/NeuralNetwork.cc src/Evolution.cc src/Evaluation.cc src/nn.cc -o nn OpenBLAS/lib/libopenblas.a -I OpenBLAS/include/ -lpthread -Iinclude/

a:
	$(CXX) -std=c++11 NeuralNetwork.cc Evolution.cc Evaluation.cc nn.cc -o nn -I /home/harrison/OpenBLAS/include/ /home/harrison/OpenBLAS/lib/libopenblas.so.0 -L/home/harrison/OpenBLAS/lib -lopenblas -lpthread 
