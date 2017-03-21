#include "Evaluation.h"
#include "NeuralNetwork.h"
#include <cstdlib>
#include <random>
#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>



unsigned char* Evaluation::labels;
unsigned char** Evaluation::images;


void Evaluation::EvaluateFull()
{
	int correct = 0;
	for(int i = 0; i< 60000; i++){
		setInputNeurons(i);
		network->feedForward();

		if(getOutputNum() == labels[i])
			correct++;
	}
	
	percentCorrectFull = (double) correct / 60000.0;
}

void Evaluation::Evaluate()
{
//	network->Dump();	
	int correct = 0;
	srand(time(NULL));
	for(int i = 0; i < 64; i++){	
		int r = rand() % 60000;	
	
		setInputNeurons(r);	

	
		network->feedForward();
		
		if(getOutputNum() == labels[r])
			correct++;

		
	}
	percentCorrect = (double) correct / 64.0;
		
}


void Evaluation::setInputNeurons(int trainingPass){
	if(NeuralNetwork::numInputNeurons != 784)
		throw std::runtime_error("input neurons");
	for(int i = 0; i < NeuralNetwork::numInputNeurons; i++){
		network->setNeuronOutput(i, images[trainingPass][i]/255.0);
	}	
}


void Evaluation::createTestSet(){
}


int Evaluation::reverseInt(int i){
	unsigned char c1, c2, c3, c4;
	c1 = i & 255;
	c2 = (i >> 8) & 255;
	c3 = (i >> 16) & 255;
	c4 = (i >> 24) & 255;

	return ((int)c1 << 24) + ((int)c2 << 16) + ((int)c3 << 8) + c4;
}

unsigned char* Evaluation::readMnistLabels(std::string path){
	std::ifstream file(path);
	
	if(file.is_open()) {
		int magicNumber = 0;
		file.read((char*)&magicNumber, sizeof(magicNumber));
		magicNumber = reverseInt(magicNumber);
		
		if(magicNumber != 2049)
			throw std::runtime_error("MNIST Label: Invalid file: incorrect magic number");

		int numLabels;
		file.read((char *)&numLabels, sizeof(numLabels));
		numLabels = reverseInt(numLabels);

		if(numLabels != 60000)
			throw std::runtime_error("num labels off");


		static uchar* data = new uchar[numLabels];
		for(int i = 0; i < numLabels; i++){
			file.read((char *)&data[i], 1);
		}

		return data;
	} else {
		throw std::runtime_error("Unable to open file " + path);
	}
}

unsigned char** Evaluation::readMnistImages(std::string path){
	
	std::ifstream file(path);

	if(file.is_open()){
		int magicNumber = 0, numRows = 0, numCols = 0;

		file.read((char *)&magicNumber, sizeof(magicNumber));
		magicNumber = reverseInt(magicNumber);

		if(magicNumber != 2051)
			throw std::runtime_error("MNIST Images: Invalid file: incorrect magic number");
		int numImages;

		file.read((char *)&numImages, sizeof(numImages));
		numImages = reverseInt(numImages);

		if(numImages != 60000)
			throw std::runtime_error("num Images off");

		file.read((char *)&numRows, sizeof(numRows));
		numRows = reverseInt(numRows);

		file.read((char *)&numCols, sizeof(numCols));
		numCols = reverseInt(numCols);

		int imageSize = numRows * numCols;
		
		if(imageSize!=784)
			throw std::runtime_error("Image size off");

		static uchar** data = new uchar*[numImages];
		for(int i = 0; i < numImages; i++){
			data[i] = new uchar[imageSize];
			file.read((char *)data[i], imageSize); // FIXME
		}

		return data;
	} else {
		throw std::runtime_error("cannot open file " + path);
	}
}



void Evaluation::Test(){
	labels = readMnistLabels("/home/harrison/git-repos/NeuralNetworkCPU/datasets/MNIST/train-labels-idx1-ubyte");
	images = readMnistImages("/home/harrison/git-repos/NeuralNetworkCPU/datasets/MNIST/train-images-idx3-ubyte");

	for(int i = 0; i < 100; i++){
		std::cout << (double) labels[i] << "\n";
	}

	for(int i = 0; i < 100 ; i++){
	//	std::cout << (double) images[i] << "\n";
	}

}



int Evaluation::getOutputNum(){
	int numn = NeuralNetwork::numOutputNeurons;

	if(numn != 10)
		throw std::runtime_error("num outputs");
	
	double nums[10];
	int total = NeuralNetwork::totalNeurons;
	int highest = -1;
	for(int i = 0; i< numn; i++){
		if(network->getOutput(total-numn+i)>network->getOutput(total-numn+highest))
		//if(Clamp(network->getOutput(total-numn+1)))
			highest = i;
	}

	return highest;
}


int Evaluation::Clamp(double o){
	if(o > 0.5){
		return 1.0;
	} else {
		return 0.0;
	}
}
