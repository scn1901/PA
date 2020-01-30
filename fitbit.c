#include "fitbit.h"

void sort(Fitbit fitbitArr[DATAMAX], FILE *data){
	int h = 0, isDuplicate = 0;
	char *dataLine = NULL;
	char *element = NULL;

	//trash value for first line 
	dataLine = (char*)malloc(LINEMAX);
	fgets(dataLine, LINEMAX, data);
	while (fgets(dataLine, LINEMAX, data)){
		isDuplicate = 0;
		
		//printf("%d: %s", h, dataLine);
		//0 (patient)
		element = strtok(dataLine, ",");
		
		if(!strcmp(element, PATIENT)){
			printf("patient %d", h);
			strcpy(fitbitArr[h].patient, element);
			printf(" %s", fitbitArr[h].patient);
			//1 (minute)
			element = strtok(NULL, ",");

			for (int j = h - 1; j >= 0; --j) {
				if (!strcmp(element, fitbitArr[j].minute))
					isDuplicate = 1;
			}
			
			if (!isDuplicate) {

				strcpy(fitbitArr[h].minute, element);
				printf(" %s",fitbitArr[h].minute);
				//2 (calories)
				element = strtok(NULL,",");
				printf(" %s", element);
				fitbitArr[h].calories = atof(element);
				printf(" %lf", fitbitArr[h].calories);

				//3 (distance)
				element = strtok(NULL,",");
				fitbitArr[h].distance = atof(element);
				printf(" %lf ", fitbitArr[h].distance);

				//4 (floors)
				element = strtok(NULL,",");
				fitbitArr[h].floors = charToNum(element);
				printf("%u ", fitbitArr[h].floors);

				//5 (heartRate)
				element = strtok(NULL,",");
				fitbitArr[h].heartRate = charToNum(element);
				printf("%u ", fitbitArr[h].heartRate);

				//6 (steps)
				element = strtok(NULL,",");
				fitbitArr[h].steps = charToNum(element);
				printf("%u ", fitbitArr[h].steps);

				//7 (sleepLevel)
				element = strtok(NULL,",");
				fitbitArr[h].sleepLevel = charToNum(element);
				printf("%u\n", fitbitArr[h].sleepLevel);
				h++;
			}
		}
	}
}

unsigned int charToNum(char *string){
	unsigned int result = 0;

	result = atoi(string);

	return result;
}

double charToDouble(char *string){
	char *digit;
	char decimal[LINEMAX] = {""};
	double result = 0, dec = 0, u = 0, base = 10;
	int i = 1;
	digit = strtok(string, ".");
	result = atof(digit);
	strcpy(NULL, decimal);

	for (; i < strlen(string);i++){
		u = -1*(i);
		
		dec += atof(&decimal[i]) * (double)pow(base,u);
	}
	return result;
}

void calculate(Fitbit fitbitArr[DATAMAX], double *totalCal, double *totalDist, unsigned int *totalFloor, unsigned int *totalStep, double *aveHR, int *maxSteps, int *sleep){
	int i = 0, setMaxStep = 0, sleepCount[4] = {0}, sleepMax = 0, count = 0;
	double totalHR = 0;

	setMaxStep = fitbitArr[0].steps;

	for (; i < DATAMAX; i++){
		*totalCal += fitbitArr[i].calories;
		*totalDist += fitbitArr[i].distance;
		*totalFloor += fitbitArr[i].floors;
		*totalStep += fitbitArr[i].steps;
		totalHR += fitbitArr[i].heartRate;
		if (fitbitArr[i].steps > setMaxStep){
			setMaxStep = fitbitArr[i].steps;
		}
		sleepCount[fitbitArr[i].sleepLevel] += 1;
	}
	*aveHR = totalHR / DATAMAX;
	*maxSteps = setMaxStep;
	for (i = 0; i < 4; i++){
		if(sleepCount[i] > sleepMax){
			sleepMax = sleepCount[i];
			count = i;
		}
	}
	*sleep = count;
}

void writeOut(double totalCal, double totalDist, unsigned int totalFloor, unsigned int totalStep, double aveHR, int maxSteps, int sleep, FILE *outfile){
	fprintf(outfile, "Total Calories 	Total Distance 	Total Floors 	Total Steps 	Average HeartRate 	Max Steps 	Sleep Level\n");
	fprintf(outfile, "	%lf				%lf				%u 				%u 				%lf				%d 				%d", totalCal, totalDist, totalFloor, totalStep, aveHR, maxSteps, sleep);
}