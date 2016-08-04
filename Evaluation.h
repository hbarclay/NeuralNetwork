

#ifndef SRC_EVALUATION
#define SRC_EVALUATION

#include "NeuralNetwork.h"


class Evaluation {

	double percentCorrect;


public:
	NeuralNetwork* network;
	int id;
	int testSetSize = 30000;

	int val1[30000];
	int val2[30000];
	int val3[30000];	

	void Evaluate();
	void setInputNeurons();
	void createTestSet();
	
	double getPercentCorrect() {
		return percentCorrect;
	}


};


#endif
