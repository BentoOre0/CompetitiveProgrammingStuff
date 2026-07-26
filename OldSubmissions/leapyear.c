#include <stdio.h>
#include <stdlib.h>


int main(){
    printf("Please enter a year: ");
    int year;
    scanf("%d", &year);

    if(year < 1582){
        printf("The Gregorian Calendar had not been adopted at that time");
    } else {
        if(year % 4 == 0){
            if(year % 100 == 0 && year % 400 != 0){
                printf("%d is not a leap year", year);
            } else {
                printf("%d is a leap year", year);
            }
        } else {
            printf("%d is not a leap year", year);
        }
    }
    
}