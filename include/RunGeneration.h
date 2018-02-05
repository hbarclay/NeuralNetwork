#ifndef INCLUDE_RUN_GENERATION_H_
#define INCLUDE_RUN_GENERATION_H_


class RunGeneration {


 public:
	RunGeneration() : evaluations(evaluations_) { buildDataArrays(); }

	void launchEvals();	
	void syncResults();	

	std::vector<std::unique_ptr<Evaluation>> getResultsVec() { return evaluations; }
	
	std::vector<std::unique_ptr<Evaluation>> evaluations;	


 private:	
	void buildDataArrays();

	// final built arrays 
	float outputs[];
	float weights[];
	float biases[];
};


#endif  // INCLUDE_RUN_GENERATION_H_
