#include <stdio.h>
#include <stdlib.h>

/*
Author: Jeremy Aidan Yu
Date: October 20, 2025
Purpose: implement a rangechecker for input as a function
*/


int getInputInRange(int min, int max){
    int inputs;
    do{
        printf("Please enter an integer between %d and %d inclusive: ", min, max);
        scanf("%d", &inputs);
        if(inputs < min || inputs > max){
            printf("Error: input not in range!\n");
        }

    } while(inputs < min || inputs > max);
    return inputs;
}
