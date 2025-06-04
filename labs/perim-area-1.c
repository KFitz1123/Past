/* program to compute the perimeter and area of a rectangle */

#include <stdio.h>

/* function to compute the perimeter of a rectangle, 
   given the lengths of the two sides */
double
calculate_perimeter (double side1, double side2)
{
  double lengthPlusWidth = side1 + side2;
  printf ("parameter side1:  location: %p, value: %lf\n",
       &side1, side1);
printf ("parameter side2:  location: %p, value: %lf\n", 
       &side2, side2);
printf ("local lengthPlusWidth:  location: %p, lengthPlusWidth: %lf\n", 
       &lengthPlusWidth, lengthPlusWidth);
  return 2.0 * lengthPlusWidth;
} // calculate_perimeter


/* function to compute the area of a rectangle, 
   given the lengths of the two sides */
double
calculate_area (double side1, double side2)
{
  printf ("parameter side1:  location: %p, value: %lf\n", 
       &side1, side1);
printf ("parameter side2:  location: %p, value: %lf\n", 
       &side2, side2);
  return side1 * side2;
} // calculate_area


/* demonstrate value passing by calling compute functions and
   displaying results */
int
main (void)
{
  /* declare rectangle's size */
  double length = 5.0;
  double width  = 7.0;

  /* print header */
  printf ("working with a rectangle of width %lf and length %lf\n",
          width, length);
 
  /* compute desired quantities */
  double perimeter = calculate_perimeter (length, width);
  double area  = calculate_area (length, width);

  /* print results */
  printf ("the rectangle's perimeter is %lf\n", perimeter);
  printf ("the rectangle's area is %lf\n", area);
printf ("variable length:  location: %p, value: %lf\n",
       &length, length);
printf ("variable width:   location: %p, value: %lf\n",
       &width, width);
printf ("variable perim:   location: %p, value: %lf\n",
       &perimeter, perimeter);
printf ("variable area:    location: %p, value: %lf\n", 
       &area, area);
  return 0;
} // main
