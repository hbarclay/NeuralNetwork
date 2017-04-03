#ifndef INCLUDE_EVALUATION_H_
#define INCLUDE_EVALUATION_H_

#include "NeuralNetwork.h"
#include <string>

class Evaluation {

	typedef unsigned char uchar; 

	double percentCorrectFull = 0;
	double percentCorrect;
	static int reverseInt(int i);
	int getOutputNum();
	int Clamp(double o);


public:
	NeuralNetwork* network;
	int id;
	int testSetSize = 60000;
	
	
	static uchar* labels;
	static uchar** images;
	
	static uchar* readMnistLabels(std::string path);
	static uchar** readMnistImages(std::string path);
	
	
	void Test();
	void Evaluate();
	void EvaluateFull();
	void setInputNeurons(int trainingPass);
	void createTestSet();
	
	double getPercentCorrect() {
		return percentCorrect;
	}

	double getPercentCorrectFull() {
		return percentCorrectFull;
	}


};


#endif  // INCLUDE_EVALUATION_H_
