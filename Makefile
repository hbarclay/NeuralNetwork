
.PHONY: clean nn

nn:
	$(CXX) -std=c++11 NeuralNetwork.cc Evolution.cc Evaluation.cc nn.cc -o nn /home/harrison/OpenBLAS/lib/libopenblas.a -I /home/harrison/OpenBLAS/include/ -lpthread

a:
	$(CXX) -std=c++11 NeuralNetwork.cc Evolution.cc Evaluation.cc nn.cc -o nn -I /home/harrison/OpenBLAS/include/ /home/harrison/OpenBLAS/lib/libopenblas.so.0 -L/home/harrison/OpenBLAS/lib -lopenblas -lpthread 
