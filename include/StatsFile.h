#ifndef INCLUDE_STATSFILE_H_
#define INCLUDE_STATSFILE_H_

#include <string>
#include <fstream>
#include <iostream>

class StatsFile
{

public:
	StatsFile(std::string filename_):
		filename(filename_) 
	{
		// create file and write config data
		outfile.open(filename);
		if (!outfile)
			std::cerr << "cannot open output file!" << std::endl;
		outfile << "runstats....\n";	
		outfile.flush();
	}

	~StatsFile() { outfile.close(); }
		

	std::string filename;
	std::ofstream outfile;	

	void WriteGeneration(int genNumber, double bestTestPerformer, double bestRealPerformer);
};


#endif // INCLUDE_STATSFILE_H
