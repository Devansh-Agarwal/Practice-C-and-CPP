#include <stdio.h>
char name_day[7][10]= {"SUNDAY","MONDAY","TUESDAY","WEDNESDAY","THURSDAY","FRIDAY","SATURDAY"};//array for days
int calculate_day(int d,int m,int y)
{
	int days=0;
	if(m>2)
	{
		if((y%4==0&&y%100!=0)||(y%400==0))//leap year condition
			days+=1;
	}
	
	days+=((y-1)%400);
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
void main()
{
	int day,month,year;
	printf("Enter the day :");
	scanf("%d",&day);
	printf("Enter the month :");
	scanf("%d",&month);
	printf("Enter the year :");
	scanf("%d",&year);
	int a =calculate_day(day,month,year);
	printf("%s",name_day[a]);
}
