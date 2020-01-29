#include "fitbit.h"

int main(void){
	int maxSteps = 0, sleep = 0;
	double totalCal = 0, totalDist = 0, aveHR = 0;
	unsigned int totalFloor = 0, totalStep = 0;

	Fitbit FitbitData[DATAMAX] = {{"","",0,0,0,0,0,0}};

	FILE *infile, *outfile;

	infile = fopen("FitbitData.csv", "r");

	sort(FitbitData, infile);
	printf("sort");

	calculate(FitbitData, &totalCal, &totalDist, &totalFloor, &totalStep, &aveHR, &maxSteps, &sleep);
	printf("calculate");

	outfile = fopen("results.csv", "w");

	writeOut(totalCal, totalDist, totalFloor, totalStep, aveHR, maxSteps, sleep, outfile);
	printf("write");

	fclose(infile);
	fclose(outfile);
}