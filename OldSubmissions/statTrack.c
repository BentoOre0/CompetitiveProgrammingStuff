#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INT_MAX (1 << 30) + ((1 << 30) - 1)

double mean(double array[], int size);
double var(double array[], int size);
double sdev(double array[], int size);
double minimum(double array[], int size);

double mean(double array[], int size){
    long double total = 0;
    for(int i = 0; i < size; i++){
        total += (long double) array[i];
    }
    total = total / (long double) size;
    return (double) total;
}

double var(double array[], int size){
    double average = mean(array,size);
    double total = 0;
    for(int i = 0; i < size; i++){
        total += (array[i] - average)*(array[i] - average);
    }
    return total/(size-1);
}

double sdev(double array[], int size){
    return sqrt(var(array,size));
}

double minimum(double array[], int size){
    double min_val = INT_MAX;
    for(int i = 0; i < size; i++){
        if(array[i] < min_val){
            min_val = array[i];
        }
    }
    return min_val;
}