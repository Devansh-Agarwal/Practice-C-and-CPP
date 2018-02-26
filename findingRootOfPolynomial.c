#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double evaluateDerivative(double p[],double degree,double x)
{

    double derivative = 0;
    
    for(int i=0; i<degree;i++)
        derivative = derivative + ((i+1)*p[i+1]*pow(x,i));
    return derivative;

}

double evaluatePolynomial(double P[],double n,double x)
{
	double summation = 0 ;
	for(int i = 0; i<= n; i++)// evaluates given polynomial at given x
		summation = summation + (P[i] * pow(x,i));
	return summation;
}	
void main()
{
	double tolerance= 0.0001, x = 0, xPrevious, error,Fx,Fdx ;
	double n, iteration = 0;
	printf("Enter degree of Polynomial\n" );
	scanf("%lf",&n);

	if(n<1)// checking if degree is negative
	{
		printf("Invalid degree");
		return;
	}
	
	double * poly = (double*) malloc(sizeof(double) * (n+1));// dynamically allocating array of size degree +1 for Fx

	printf("Enter Coefficients one by one\nIn the format ::\na0 + a1X + a2X^2 + ...+ anX^n\n");

	for(int i = 0; i <= n; i++ )// scanning polynomial
	{
		printf("Enter a%d\n",i);
		scanf("%lf",&poly[i]);
	} 

			
	xPrevious = x;
	do 
	{
		Fx = evaluatePolynomial(poly, n, x);// calculating value of function at x
		Fdx = evaluateDerivative(poly, n, x);// calculating derivative of function at x
		if(Fdx == 0)
		{
			printf("Root does not exist.\n");
			return;
		}
		x = x - (Fx / Fdx) ;
		error = fabs(x - xPrevious); // calculating error
		xPrevious = x;
		
		iteration ++;
		if(iteration >= 10000)// if more than 10000 iterations function doesnt converge
		{
			printf("Root doesn't exist.\n");
			return;
		}
	}while(error > tolerance);

	printf("root = %.2f \n", x);// printing to 2 the 2nd decimal place

}