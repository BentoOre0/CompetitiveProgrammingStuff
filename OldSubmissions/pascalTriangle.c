#include <stdio.h>
#include <stdlib.h>

/*
Author: Jeremy Aidan Yu
Date: October 20, 2025
Purpose: print a pascals triangle with single space seperators
*/

#define MIN 1
#define MAX 12
int factorial(int n){
    if(n == 0){
        return 1;
    }
    int i = 1;
    int prod = 1;
    while(i <= n){
        prod *= i;
        i++;
    }
    return prod;
}

int choose(int n, int r){
    return factorial(n)/(factorial(r))/factorial(n-r);
}

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

int main(){

    int userInput = getInputInRange(MIN,MAX);
    for(int i = 0; i <= userInput; i++){
        for(int j = 0; j <= i; j++){
            printf("%d ", choose(i,j));
        }
        printf("\n");
    }
}