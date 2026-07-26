#include <stdio.h>
#include <stdlib.h>

#define min(a,b) (a < b) ? (a) : (b)
int main(){
    printf("Please enter the price of a new home: ");
    
    int price;
    scanf("%d", &price);

    if(price < 0){
        printf("The house price cannot be negative.");
    } else {
        double purchase_price = price;
        double gross = 0.05*purchase_price;
        double rebate = 0;

        if(purchase_price<= 350000){
            rebate = min(0.36*gross,5000.00);
        } else if(purchase_price <= 450000){
            rebate = 5000.00 * (450000.00-purchase_price)/(1e5);
        }
        //else rebate stays 0

        double GST = gross - rebate;
        
        printf("GST is %lf", GST);



    }
    return 0;
}