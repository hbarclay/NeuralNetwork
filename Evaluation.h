

#ifndef SRC_EVALUATION
#define SRC_EVALUATION

#include "NeuralNetwork.h"


class Evaluation {

	double percentCorrect;


public:
	NeuralNetwork* network;
	int id;

	void Evaluate();
	
	double getPercentCorrect() {
		return percentCorrect;
	}


};


#endif
