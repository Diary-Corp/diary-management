//
// Created by flasque on 11/10/2023.
//

#include <stdio.h>
#include <malloc.h>
#include "timer.h"
#include "list.h"
#include <stdlib.h>
#include "math.h"
// start the timer
void startTimer()
{
    _timer._start = clock();
}

// stop the timer and compute the duration in milliseconds
void stopTimer()
{
    _timer._end = clock();
    // compute the duration in milliseconds wrt CLOCKS_PER_SEC
    _timer._msecs = (1000.0 * (double) (_timer._end - _timer._start)) / CLOCKS_PER_SEC;
}

// display the time
void displayTime()
{
    // display the time using getTimeAsString()
    printf("%s", getTimeAsString());
    return;
}

// return a string with the time in seconds and milliseconds
char *getTimeAsString()
{
    // return a string with the time in seconds and milliseconds
    // format : integers, with 3 digits, fill with 0
    // example : 001,123

    // use sprintf to write the string in a dynamically allocated buffer
    char *buffer = (char *)malloc(10*sizeof(char));
    // use sprintf to write the string in a dynamically allocated buffer
    //sprintf(buffer, "[%g] %03d,%03d", _timer._msecs, (int)(_timer._msecs)/1000, (int)(_timer._msecs)%1000);
    sprintf(buffer, " %03d.%03d", (int)(_timer._msecs)/1000, (int)(_timer._msecs) % 1000);

    // return the buffer
    return buffer;
}

void complexityTest(){
    int maxN, N;

    printf("Enter the maximum number of levels in the list: ");
    scanf("%d", &maxN);
    printf("%d levels in list. \n", maxN);
    int iter;
    printf("Enter the number of iterations: ");
    scanf("%d", &iter);
    printf("\n Standard non-level search: \n");
    printf("[");
    for(N = 1; N<maxN; N++) {
        // Create a list with a single level
        t_d_list *myList = createList(N);

        // Insert N numbers into the list
        int counter = 1;
        for (int i = 1; i <= pow(2, N) - 1; i++) {
            t_d_cell *newCell = createCell(i, myList->max_levels);
            insertCell(myList, newCell);
            counter = i;
        }


        int result, i;

        startTimer(); ///start the timer
        for (i = 1; i < iter; i++) {
            int x;
            srand(time(NULL));
            x = (rand() % (counter + 1));
            result = searchValue(myList, x);
        }
        stopTimer();///stops the timer
        if(N!=1){printf(",");}
        displayTime();///display the timer
    }
    printf("]\n");
    printf("\n\n Level based search: \n");
    printf("[");
    for(N = 1; N<maxN; N++) {
        // Create a list with a single level
        t_d_list *myList = createList(N);

        // Insert N numbers into the list
        int counter = 1;
        for (int i = 1; i <= pow(2, N) - 1; i++) {
            t_d_cell *newCell = createCell(i, myList->max_levels);
            insertCell(myList, newCell);
            counter = i;
        }


        int result, i;

        startTimer(); ///start the timer
        for (i = 1; i < iter; i++) {
            int x;
            srand(time(NULL));
            x = (rand() % (counter + 1));
            result = searchLevelValue(myList, x);
        }
        stopTimer();///stops the timer
        if(N!=1){printf(",");}
        displayTime();///display the timer
    }
    printf("]\n");
}