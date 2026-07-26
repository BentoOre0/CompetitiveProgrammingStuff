#include <stdio.h>
#include <stdlib.h>

int main(){
    double start_temp, temperature_increment;
    int number_of_conversions;
    printf("Please enter starting tempeprature in degrees Celsius: ");
    scanf("%lf", &start_temp);

    printf("Please enter the increment: ");
    scanf("%lf", &temperature_increment);

    do {
        printf("Please enter the number of temperatures to convert: ");
        scanf("%d", &number_of_conversions);

        if(number_of_conversions <= 0){
            printf("Error: number of temperatures to convert is non positive.\n");
        }
    } while(number_of_conversions <= 0);
    

    int i = 0;
    double temperature_celsius = start_temp;
    while(i < number_of_conversions){
        double temperature_farenheit = 9*temperature_celsius/5 + 32.0;
        printf("%.2lf%9.2lf\n", temperature_celsius, temperature_farenheit);
        temperature_celsius += temperature_increment;
        i++;
    }

   
}