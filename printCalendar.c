#include <stdio.h>
char month_name[12][9]= {"January","February","March","April","May","June","July","August","September","October","November","December"};
char name_day[7][3]= {"Su","Mo","Tu","We","Th","Fr","Sa"};
int calculate_day(int d,int m,int y)
{
	int days=0;
	if(m>2)
	{
		if((y%4==0&&y%100!=0)||(y%400==0))//leap year condition
			days+=1;
	}
	
	days+=((y-1)%400)*365;
	y=y%400;
	days=days +(y-1)/4;//adding leap years
	if (y>=100&&y<200)//removing extra years
	{
		days--;
	}
	if (y>=200&&y<300)//removing extra years
	{
		days = days-2;
	}
	if (y>=300)//removing extra years
	{
		days= days- 3;
	}
	days= days + (m-1)*28;//adding days from months
	
	if(m>2)//adjusting offsets from 28
	{
		if(m>7)
		{
			days=days+13;
			m=m-5;
		}
		if((m-3)%2==0)
		{
			days =days+ ((m-3)/2)*5 +3;
		}	
		if((m-3)%2==1)
		{
			days= days+ ((m-3)/2)*5 +6;
		}	
	}
	if(m==2)
		days= days+3;
		
		
	days = (days + d)%7;//calculating the day 

	return days;

}

void tripple_month(int a , int b,int c,int y)//prints three months at a time
{	int w[]={0,0};
	int x,y2,z;
	int a1=1,b1=1,c1=1,g=1,s=0,aa=0;	
	int d[]={calculate_day(1,a,y),calculate_day(1,b,y),calculate_day(1,c,y)};
	for(int j=0;j<3;j++)// printing name of days
	{
		for(int k=0;k<7;k++)
		{
			printf("%s ",name_day[k]);
		}
	printf(" ");
	}
	printf("\n");	
	
	if((a<8&&a%2==1)||(a>7&&a%2==0))//checking for number of days in the 1st month
		x=31;
	else
		if((a<8&&a%2==0&&a!=2)||(a>7&&a%2==1))
			x=30;
		else
			x=28;
		if(((y%4==0&&y%100!=0)||(y%400==0))&&a==2)
		x++;
	if((b<8&&b%2==1)||(b>7&&b%2==0))//checking for number of days in the 2nd month
		y2=31;
	else
		if((b<8&&b%2==0&&b!=2)||(b>7&&b%2==1))
			y2=30;
		else
			y2=28;
		if(((y%4==0&&y%100!=0)||(y%400==0))&&b==2)
		y2++;
	if((c<8&&c%2==1)||(c>7&&c%2==0))//checking for number of days in the 3rd month
		z=31;
	else
		if((c<8&&c%2==0&&c!=2)||(c>7&&c%2==1))
			z=30;
		else
			z=28;
		if(((y%4==0&&y%100!=0)||(y%400==0))&&c==2)
			z++;
	for(int k =0;k<d[0];k++)
		printf("   ");
	while(1)
	{
		if(a1<=x&&b1>y2)
			aa++;
		if(a1<=x)
			do{//printing line by line 1st month
				if(a1<10)
					printf(" %d ",a1);
				else
					printf("%d ",a1);
				a1++;
				d[0]=d[0]%7;
				++d[0];
				}while((d[0])%7!=0&&a1<=x);
		printf(" ");
		if(a1>x&&b1<=y2)
		{	
			if(s==1)
					printf("                     ");
			if((s++)==0)
				for(int k =0;(k<7-d[0]);k++)
					printf("   ");
				
		}
		if (w[0]==0)// taking care of spaces in 1st line of month
			for(int k =0;k<d[1];k++)
				printf("   ");
		w[0]++;	
		if(b1<=y2)
			do{//printing line by line 2nd month
				if(b1<10)
					printf(" %d ",b1);
				else
					printf("%d ",b1);
				b1++;		
				d[1]=d[1]%7;
				++d[1];
				}while((d[1])%7!=0&&b1<=y2);
		printf(" ");
		if (w[1]==0)// taking care of spaces in 1st line of month
			for(int k =0;k<d[2];k++)
				printf("   ");
		w[1]++;	
		if(a1>x&&b1>y2&&g==0)
		{	
			if(aa==0)
				printf("                                          ");//providing spaces for the last month if 2nd and 1st both are over
			if(aa!=0)
				printf("                     ");//providing spaces for the last month if 2nd is over but not 1st
		}
		if(b1>y2&&g==1)
		{
			for(int k =0;(k<7-d[1]);k++)
			printf("   ");
			g--;
		}
		
		if(c1<=z)
			do{//printing line by line 3rd month
				if(c1<10)
					printf(" %d ",c1);
				else
					printf("%d ",c1);
				c1++;
				d[2]=d[2]%7;
				++d[2];
				}while((d[2])%7!=0&&c1<=z);
		printf("\n");
		if(a1>x&&b1>y2&&c1>z)
			break;
}}

void year(int y)
{
	printf("                               %d\n",y);
	printf("      January                February                March\n");
	tripple_month(1,2,3,y);
	printf("\n\n                               %d\n",y);
	printf("      April                 May                   June\n");
	tripple_month(4,5,6,y);
	printf("\n\n                               %d\n",y);
	printf("      July                  August                September\n");	
	tripple_month(7,8,9,y);
	printf("\n\n                               %d\n",y);
	printf("      October                November             December\n");
	tripple_month(10,11,12,y);
	printf("\n");
}
void month(int m , int y)
	{
		int day = calculate_day(1,m,y); 
		printf("      %s\n",month_name[m-1]);

		for(int i=0;i<7;i++)
			{
				printf("%s ",name_day[i]);
	}
	printf("\n");
	int i =0;
	if((m<8&&m%2==1)||(m>7&&m%2==0))
		i=31;
	else
		if((m<8&&m%2==0&&m!=2)||(m>7&&m%2==1))
			i=30;
		else
			i=28;
		if(((y%4==0&&y%100!=0)||(y%400==0))&&m==2)
		i++;
	for(int k =0;k<day;k++)
		printf("   ");


	for(int j=1;j<=i;j++)
	{
		if(j<10)
			printf(" %d ",j);
		else
			printf("%d ",j);
		if((++day)%7==0)
			printf("\n");
	day=day%7;
	}
	printf("\n");	}
	void main()
	{
		int choice,Y=0,M=0,YM=0,J=0;
		while(1)
		{
			printf("Calendar Menu:\n1. Display year\n2. Display month\n3. Move right\n4. Move Left\n5. Exit\n");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1:
						printf("Enter year\n");
						scanf("%d",&Y);
						if(Y==0)
							{
								printf("year cant be zero\n");
								break;
							}
						year(Y);
						M=0;
						break;
				case 2:
						printf("Enter month and year\n");
						scanf("%d%d",&M,&YM);		
						if(YM==0||M==0)
							{
								printf("year or month cant be zero\n");
								break;
							}
						month(M,YM);
						Y=0;
						break;
				case 3 : 
						if(Y!=0)
						{
							year(++Y);
						}
						if(YM!=0&&M!=0)
						{
							if(M<12)
							month(++M,YM);
							if(M==12)
							month(1,++YM);
						}
						break;
				case 4 :if(Y!=0)
						{
							year(--Y);
						}
						if(YM!=0&&M!=0)
						{
							if(M>1)
							month(--M,YM);
							if(M==1)
							month(12,--YM);
						}
						break;
				case 5 :
						J=1;
						break;
				default:
						printf("Enter correct choice\n");
						break;									
			}
			if(J==1)
				break;

		}
	}