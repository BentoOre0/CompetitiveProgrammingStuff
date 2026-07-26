/*
 * Author:       Jeremy Aidan Yu
 * Date:         September 24, 2025
 * Student ID:	 19743475
 * Lab Section:  L1J 
 * UBC e-mail:   jahy2025@student.ubc.ca
 *
 * Purpose:      Prompt the user for a force in Newtons
 *               Compute the equivalent force in pounds
 *               Print the equivalent force in pounds to 3 decimal places
 */

#include <stdio.h>
#include <stdlib.h>

#define NEWTONS_TO_POUND 1/4.448  //the ratio

int main( void ) {
  double force_nt, force_lb;
  
  printf("Please enter a non-negative value of Force in Newtons: ");
  scanf("%lf", &force_nt);

  force_lb = force_nt*NEWTONS_TO_POUND;
  
  printf("The equivalent force in pounds is: %.3lf lbs", force_lb);
  
  return 0;
}