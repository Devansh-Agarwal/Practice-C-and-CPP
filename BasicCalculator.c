#include <stdio.h>
void Add()
{
	long int num1,num2;
	printf("Enter first number\n");
	scanf("%ld",&num1);
	printf("Enter second number\n");
	scanf("%ld",&num2);
	printf("The result of the operation is %ld\n",(num1 + num2));
}
void Subtract()
{
	long int num1,num2;
	printf("Enter first minuend\n");
	scanf("%ld",&num1);
	printf("Enter second subtrahend\n");
	scanf("%ld",&num2);
	printf("The result of the operation is %ld\n",(num1 - num2));
}
long int multiply(long int num1,long int num2)
{
	long int small,mull=0 ;
	if(num1>=num2)
		small = num2;
	else
		small = num1;
	for(long int i =0;i<small;i++)//choosing the smaller loop
		mull= mull + (num1+num2-small);
	return mull;
}
long int divide(long int num1,long int num2)//num1 is dividend ,num2 is divisor
{
	long int quotient=0 ;
	while(1)
	{
		if(num1-num2>=0)//this works only for floor
		{
			num1-=num2;
			quotient++;
		}
	 	else
	 		break;
	}
	return quotient ;
}
long int modulus(long int num1,long int num2)//num1 is dividend ,num2 is divisor
{
	
	while(1)
	{
		if(num1-num2>=0)// this works only for floar
		{
			num1-=num2;
		}
	 	else
	 		return num1;
	}
	 
}
long int square(long int num1)
{
	long int square=0;
	for(long int i=0;i<num1;i++)
	{
		square=square+num1;// caluculating square by  adding num1, num1 times
	}
return square;
}
long int square_root(long int num1)
{long int up;
	for(long int i =0;i<num1/2;i++)
	{
		up = square(i);
		if(up==num1)
			return i;
		if(up>num1)
			return i-1;
	}
}
long int Log(long int num1)//works for only ceil
{
	long int a=1,count=0;
	if(num1<=1)
		return 0;
	while(1)
	{
		a=multiply( a,2); // using multiply function 
		count++;//calculating to which power of a is num1 lesser than
		if(num1<=a)
			return count;
	}
	}
void main()
{
	long int choice,a,b;
	while(1)
	{
		printf("Menu:\n1) Add\n2) Multiply\n3) Divide\n4) Subtract\n5) Modulus\n6) Square\n7) Square root\n8) Log\n9) Exit\n");// printing menu
		scanf("%ld",&choice);
		if (choice==1)
		{
			Add();
			continue;
				}
				else
					if(choice==2)
					{
						printf("Enter first number\n");
						scanf("%ld",&a);
						printf("Enter second number\n");
						scanf("%ld",&b);
						printf("The result of the operation is %ld\n",multiply(a,b));
						continue;

					}
					else
						if(choice==3)
						{
							printf("Enter  dividend\n");
							scanf("%ld",&a);
							printf("Enter  divisor\n");
							scanf("%ld",&b);
							if(b==0)
								{
									printf("divisor can't be zero\n");
									continue;
								}
							printf("The result of the operation is %ld\n",divide(a,b));
							continue;
						}
						else
							if(choice==4)
							{
								Subtract();
								continue;
							}
							else
								if(choice==5)
								{
									printf("Enter  dividend\n");
									scanf("%ld",&a);
									printf("Enter  divisor\n");
									scanf("%ld",&b);
									if(b==0)
									{
										printf("divisor can't be zero\n");
										continue;
									}
									printf("The result of the operation is %ld\n",modulus(a,b));
									continue;								
								}
								else
									if(choice==6)
									{
										printf("Enter  number\n");
										scanf("%ld",&a);
										printf("The result of the operation is %ld\n",square(a));
										continue;
									}
									else
										if(choice==7)
										{
											printf("Enter  number\n");
											scanf("%ld",&a);
											printf("The result of the operation is %ld\n",square_root(a));
											continue;
										}
										else
											if(choice==8)
											{
												printf("Enter  number\n");
												scanf("%ld",&a);
												if(a==0)
													{
														printf("invalid input!!\n");
														continue;
													}
												printf("The result of the operation is %ld\n",Log(a));
												continue;
											}
											else
												if(choice==9)
												break;
	printf("INVAID INPUT!! Please re-enter your choice\n");	// will only activate if none of the above activate		

	}
}