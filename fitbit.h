#ifndef FITBIT
#define FITBIT

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define ELEMENTS 11520
#define DATAMAX 1460
#define LINEMAX 200
#define DATANUM 8
#define PATIENT "12cx7"

typedef enum sleep{
    NONE = 0, ASLEEP = 1, AWAKE = 2, REALLYAWAKE = 3
} Sleep;

typedef struct fitbit {
    char patient[10];
    char minute[9];
    double calories;
    double distance;
    
    unsigned int floors;
    unsigned int heartRate;
    unsigned int steps;
    Sleep sleepLevel;
} Fitbit;

/**************************************
* Function name: structDef
* Date created: 01.19.2020
* Date edited: 01.19.2020
* Description: initializes the struct
    array before using it
* Input parameters: address of the
    first element of array "FitbitData"
* Returns: nothing
* Preconditions: function "structDef"
    is called
* Postconditions: "FitbitData" array is
    defined
***************************************/
void structDef(Fitbit fitbitArr[DATAMAX]);
/**************************************
* Function name: sortData
* Date created: 01.19.2020
* Date edited: 01.23.2020
* Description: goes through each line in
    the csv file, sorts through the data
    and saves it into a struct
* Input parameters: address of the
    first element of array "FitbitData",
    address of the csv file holding the
    fitbit data
* Returns: nothing
* Preconditions: function "sortData"
    is called
* Postconditions: struct should be completely
    filled
***************************************/
void sort(Fitbit fitbitArr[DATAMAX], FILE *data);
/**************************************
* Function name: charToNum
* Date created: 01.19.2020
* Date edited: 01.23.2020
* Description: turn string into unsigned int
* Input parameters: character array
    of a number, pointer to an unsigned
    integer to store the number
* Returns: nothing
* Preconditions: switch condition 5, 6, 7
* Postconditions: an unsigned int is saved
    into struct
***************************************/
unsigned int charToNum(char *string);
/**************************************
* Function name: charToDouble
* Date created: 01.19.2020
* Date edited: 01.23.2020
* Description: turn string into double
* Input parameters: char star (string)
* Returns: unsigned int
* Preconditions: switch condition 3, 4
* Postconditions: a double is saved
    into struct
***************************************/
double charToDouble(char *string);
/**************************************
* Function name: calculateData
* Date created: 01.19.2020
* Date edited: 01.23.2020
* Description: add up data
* Input parameters: char star (string)
* Returns: double
* Preconditions: function called
* Postconditions: array "total" will
    have the calculated values of the
    struct
***************************************/
void calculate(Fitbit fitbitArr[DATAMAX], double *totalCal, double *totalDist, unsigned int *totalFloor, unsigned int *totalStep, double *aveHR, int *maxSteps, int *sleep);
/**************************************
* Function name: writeData
* Date created: 01.19.2020
* Date edited: 01.23.2020
* Description: write data into output
    file
* Input parameters: calculated data variables,
    address of output file
* Returns: nothing
* Preconditions: function called
* Postconditions: calculated values will
    be saved into the output file
***************************************/
void writeOut(double totalCal, double totalDist, unsigned int totalFloor, unsigned int totalStep, double aveHR, int maxSteps, int sleep, FILE *outfile);

#endif