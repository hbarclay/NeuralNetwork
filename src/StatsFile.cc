// StatsFile
#include "StatsFile.h"

#include <fstream>


void StatsFile::WriteGeneration(int genNumber, double bestTestPerformer, double bestRealPerformer)
{
	outfile << 
		genNumber << 
		',' << 
		bestTestPerformer << 
		',' <<
		((bestRealPerformer > 0) ? bestRealPerformer : 0) << "\n";
	outfile.flush();
}
