/*
 * Author:       Jeremy Aidan Yu
 * Date:         September 24, 2025
 * Student ID:	 19743475
 * Lab Section:  L1J 
 * UBC e-mail:   jahy2025@student.ubc.ca
 *
 * Purpose:     
 * - The program prompts the user for the length (in metres) of each of: 
 *      - the first segment (AB) and the second segment (BC) of the robot arm
 * - The program prompts the user for theta 1
 *      - defined as the first segment of the robot arm makes with the positive x-axis, 
 *        measured counterclockwise in radians from the positive x-axis;
 * - The program prompts the user for theta 2
 *      -  defined as the angle that the second segment of the robot arm makes with the positive x-axis,
 *         measured counterclockwise in radians from the positive x-axis
 * - The program computes the coordinates of point C, and prints the coordinates of point C to 6 decimal digits.
 * - It computes given the formula:
 *  x = ABcos(theta_1) + BCcos(theta_2)
 *  y = ABsin(theta_1) + BCsin(theta_2)
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main( void ) {
  double AB, BC, theta_1, theta_2;
  double C_x, C_y;

  printf("Please enter the length of segment AB in meters: ");
  scanf("%lf", &AB);

  printf("Please enter the length of segment BC in meters: ");
  scanf("%lf", &BC);

  printf("Please enter the value of theta_1 in radians: ");
  scanf("%lf", &theta_1);

  printf("Please enter the value of theta_2 in radians: ");
  scanf("%lf", &theta_2);

  C_x = AB*cos(theta_1) + BC*cos(theta_2);
  C_y = AB*sin(theta_1) + BC*sin(theta_2);

  printf("%.6lf, %.6lf", C_x, C_y);


  return 0;
}