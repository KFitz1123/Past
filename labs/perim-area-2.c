/* program to compute the perimeter and area of a rectangle */

#include <stdio.h>

/* compute the perimeter and area of a rectangle, 
   given the lengths of the two sides */
/*void
compute (double side1, double side2, double * pPerimeter, double * pArea)
{
  double lengthPlusWidth = side1 + side2;
  *pPerimeter = 2.0 * lengthPlusWidth;
  *pArea = side1 * side2;
} // compute


/* demonstrate pointer passing by calling compute and displaying results 
int
main (void)
{
  /* declare variables 
  double length = 5.0;
  double width  = 7.0;
  double perimeter;
  double area;

  /* print header 
  printf ("working with a rectangle of width %lf and length %lf\n",
          width, length);
 
  /* compute desired quantities 
  compute (length, width, &perimeter, &area);

  /* print results 
  printf ("the rectangle's perimeter is %lf\n", perimeter);
  printf ("the rectangle's area is %lf\n", area);

  return 0;
}*/ // main
/* program to compute the perimeter and area of a rectangle */

#include <stdio.h>

/* compute the perimeter and area of a rectangle, 
   given the lengths of the two sides */
void
compute (double side1, double side2, double * pPerimeter, double * pArea)
{
  double lengthPlusWidth = side1 + side2;
  *pPerimeter = 2.0 * lengthPlusWidth;
  *pArea = side1 * side2;

  printf ("compute:  addresses, values, and pointer references\n");
  printf ("             side1:  address: %p, value: %lf\n",
          &side1, side1);
  printf ("             side2:  address: %p, value: %lf\n",
          &side2, side2);
  printf ("   lengthPlusWidth:  address: %p, value: %lf\n", 
          &lengthPlusWidth, lengthPlusWidth);
  printf ("   pPerimeter:       address: %p, value: %p, *pPerimeter: %lf\n", 
          &pPerimeter, pPerimeter, *pPerimeter);
  printf ("   pArea:            address: %p, value: %p, *pArea: %lf\n", 
          &pArea, pArea, *pArea);
} // compute


/* demonstrate pointer passing by calling compute and displaying results */
void computeCircleGeo(double *r){


  printf("Radius: %lf\n", *r);
  printf("Circomfrance: %lf\n", (*r)*(2*3.14));
  printf("Area: %lf\n", *r * *r * 3.14);


}





int main (void)
{
  double r = 5;
  computeCircleGeo(&r);

  
  /* declare variables */
  double length = 5.0;
  double width  = 7.0;
  double perimeter;
  double area;

  /* print header */
  printf ("working with a rectangle of width %lf and length %lf\n",
          width, length);

   /* compute desired quantities */
  compute (length, width, &perimeter, &area);

  /* print results */
  printf ("the rectangle's perimeter is %lf\n", perimeter);
  printf ("the rectangle's area is %lf\n", area);

  printf ("main:  variable addresses and values\n");
  printf ("   length:      address: %p, value: %lf\n", 
	 &length, length);
  printf ("   width:       address: %p, value: %lf\n", 
	 &width, width);
  printf ("   perimeter:   address: %p, value: %lf\n", 
	 &perimeter, perimeter);
  printf ("   area:        address: %p, value: %lf\n", 
	 &area, area);

  return 0;
} // main
