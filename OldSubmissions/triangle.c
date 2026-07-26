#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("Please enter a positive integer between 1 and 9 inclusive: ");
    
    int size;
    scanf("%d",&size);

    int i = 0, j = 0, count = 1;
    while(i < size){
        j = 0;
        count = 1;
        while(j < size){
            if(j >= size - i - 1){
                printf("%d",count);
                count++;
            } else {
                printf(".");
            }
            j++;
        }
        printf("\n");
        i++;
    }
}