#include <stdio.h>
#include <stdlib.h>

/*
Author: Jeremy Aidan Yu
Date: October 20, 2025
Purpose: implement factorial function
*/
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