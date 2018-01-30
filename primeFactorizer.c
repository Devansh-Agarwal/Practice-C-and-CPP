#include <stdio.h>
int num;
void main()
{
	int x=4,y=1,z=0;
	printf("Enter a number :");
	scanf("%d",&num);
	printf("The prime factors are :");
	while(num!=1)
	{
	   y = prime_factors(num); // calculating factor
       
       if(x!=y)     // a new prime factor  obtained
       {
            if(z>0) //if more than 1 factor
            {
                printf(",");
            }
            z++;
            printf("%d",y);
            x=y;           //assigning  previous factor for check condition in line 28
        }
    	num=num/y;       //removing the already known prime factors
    }
}
int prime_factors(int num)
{
	int i =2;
	while(i<=num/2)
	{
		if(num%i==0) //checking for prime factor
		{
			return i;
		}
		i++;
	}
	return num;

}

