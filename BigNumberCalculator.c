#include <stdio.h>
#include <string.h>
int num1[1500],num2[1500],result[1500],temp[1500],dividendarray[1500];
void Menu()
{
  printf("1.Add\n2.Multiply\n3.Subtract\n4.Divide\n5.Exit\n");//Printing Menu
}
int Find_Bigger_Array(int *arr1,int *arr2)//Finds the bigger array
{
  int i=0;
  while(i<1500)
  {
    if(arr1[i]<arr2[i])
     {
      return 1;
      }
      else
          if(arr1[i]>arr2[i])
          {
            return 0;
          }
    i++;
  }

  return 0; 
}
void printresult()//prints the result of calculations
{
  int i,zeroes=0;
  for(i=0;result[i]==0;i++)
  {
    zeroes++;
    
  }
  printf("\n the result is ");
  if(zeroes>=1500)
    printf("0");
  while(i<1500)
  {
    printf("%d",result[i++]);
  }
  printf("\n");
}
void subtract(int *arr1,int *arr2)//subtracts 2 numbers
{
  int i,j,carry=0;
  if(Find_Bigger_Array(arr1,arr2)==0)
  {
    for(i=1499;i>=0;i--)
    {
      if(arr1[i]<arr2[i])//handles carry overs
        {
          arr1[i]+=10;
          j=i;
          while(arr1[j-1]==0)//converts 0 to 9
          {
            arr1[j-1]=9;
            j--;
          }
          arr1[j-1]--;
        }
      result[i]=arr1[i]-arr2[i];
     }
  }
    else//swaps the 2 numbers if the answer will be negative
    {
      printf("-");
     for(i=1499;i>=0;i--)
     {
       if(arr2[i]<arr1[i])
        {
          arr2[i]+=10;
          j=i;
          while(arr2[j-1]==0)
          {
            arr2[j-1]=9;
             j--;
          }
          arr2[j-1]--;
         }
        result[i]=arr2[i]-arr1[i];
     }
    }
}
void add(int *arr1,int *arr2)//adds two numbers
{
  int i;
  int carry=0;
  for(i=1499;i>=0;i--)
  {
    result[i]=(arr1[i]+arr2[i]+carry)%10;
    carry=(arr1[i]+arr2[i]+carry)/10;
   }
 }
void multiply(int len1,int len2)//multiplies 2 numbers
{
  int i,j,zeroes=0;
  int carry=0;
  int multresult[1500];
  for(i=0;i<1500;i++)
  {
    multresult[i]=0;
  }
  for(j=1499;j>=1500-len2-1;j--)
  {
    for(i=1499;i>=1500-len1-1;i--)
      {
        temp[i-zeroes]=(num2[j]*num1[i]+carry)%10;//multiplies by hand method
        carry=(num2[j]*num1[i]+carry)/10;
      }
    add(multresult,temp);
    for(i=0;i<1500;i++)
    {
      temp[i]=0;
      multresult[i]=result[i];
    }
    zeroes++;
    carry=0;
  }
 printresult();

}
void divide(int *dividend,int *divisor)//divides 2 numbers
{
  for(int i=0; i<1500;i++)
    dividendarray[i]=0;
  int i,count=0,factor,trailingzeroes,divisionresult[1500],zeroes=0;//divides using long division algorithm
  for(i=0;i<1500;i++)
    divisionresult[i]=0;
  while(dividend[count]==0)//finds position of first digit
  {
     count++;
  }

while(count<=1499)
{
  for(i=0;i<1499;i++)
    {
      dividendarray[i]=dividendarray[i+1];//shifts the array by 1 place for carry over
    }
  dividendarray[1499]=dividend[count];
  count++;
  factor=0;
  while(Find_Bigger_Array(dividendarray,divisor)!=1)//divides using long division algorithm
  {
    subtract(dividendarray,divisor);
    factor++;
    for(i=0;i<1500;i++)
    {
      dividendarray[i]=result[i];
      result[i]=0;
     }
   }
  divisionresult[count-1]=factor;
}
 for(i=0;divisionresult[i]==0;i++)
 {
   zeroes++;
   continue;
  }
  if(zeroes>=1500)
   printf("0");
 while(i<1500)
 {
    printf("%d",divisionresult[i++]);
  }
 printf("\n");
  }

int main()
{
   int choice;
   int negative1=0,negative2=0;
   int i,j,no_of_zeroes;
   char string1[1501];
   char string2[1501];
   i=0;
   while(i<1500)
   {
      num1[i]=0;num2[i]=0;result[i]=0;temp[i]=0;
      i++;
   }
    while(1)//infinite loop
    {
    no_of_zeroes=0;
    Menu();//printing menu
    scanf("%d",&choice);
    switch(choice)
    {
     case 1:i=0;
            while(i<1500)
        {
            num1[i]=0;num2[i]=0;result[i]=0;temp[i]=0;
            i++;
        }
        printf("enter the first number\n");
        scanf("%s",string1);
        printf("enter the second number\n");
        scanf("%s",string2);
        if(strlen(string1)>1000||strlen(string2)>1000)
        {
            printf("input is too long");//handles VERY LARGE NUMBERS
            continue;
        }
        if(string1[0]!='-')
        {
        negative1=0;
        for(i=1500-strlen(string1),j=0;i<1500;i++,j++)
        {
            num1[i]=string1[j]-48;
        }
        }
        else
        {
        negative1=1;
        for(i=1501-strlen(string1),j=1;i<1500;i++,j++)
        {
            num1[i]=string1[j]-48;
        }
        }
         if(string2[0]!='-')
        {
         negative2=0;
        for(i=1500-strlen(string2),j=0;i<1500;i++,j++)
        {
            num2[i]=string2[j]-48;
        }
        }
        else
        {
         negative2=1;
        for(i=1501-strlen(string2),j=1;i<1500;i++,j++)
        {
            num2[i]=string2[j]-48;
        }
        }
            if((negative1==1)&&(negative2==1))
            {
                printf("-");
            add(num1,num2);
            }
            if((negative1==0)&&(negative2==1))
            {
              subtract(num1,num2);
            }
            if((negative1==1)&&(negative2==0))
            {
              subtract(num2,num1);
            }
            if((negative1==0)&&(negative2==0))
                add(num1,num2);

            printresult();
            break;
        case 2:
            for(i=0;i<1500;i++)
        {
            num1[i]=0;num2[i]=0;result[i]=0;temp[i]=0;
        }
        printf("enter the first number\n");
        scanf("%s",string1);
        printf("enter the second number\n");
        scanf("%s",string2);
        if(strlen(string1)>1000||strlen(string2)>1000)
        {
            printf("input is too long");//handles VERY LARGE NUMBERS
            continue;
        }

        if(string1[0]!='-')//handles negative inputs
        {
        negative1=0;
        for(i=1500-strlen(string1),j=0;i<1500;i++,j++)
        {
            num1[i]=string1[j]-48;
        }
        }
        else
        {
        negative1=1;
        for(i=1501-strlen(string1),j=1;i<1500;i++,j++)
        {
            num1[i]=string1[j]-48;
        }
        }
         if(string2[0]!='-')
        {
         negative2=0;
        for(i=1500-strlen(string2),j=0;i<1500;i++,j++)
        {
            num2[i]=string2[j]-48;
        }
        }
        else
        {
         negative2=1;
        for(i=1501-strlen(string2),j=1;i<1500;i++,j++)
        {
            num2[i]=string2[j]-48;
        }
        }
            if(strlen(string1)+strlen(string2)>1000)//handles integers that are too big
            {
                printf("output is too big");
                continue;
            }
             if(((negative1==1)&&(negative2==1))||((negative1==0)&&(negative2==0)))
             {
            multiply(strlen(string1),strlen(string2));
            }
            else
            {
                printf("-");
            multiply(strlen(string1),strlen(string2));
            }
           break;
        case 3:i=0;
            while(i<1500)
        {
            num1[i]=0;num2[i]=0;result[i]=0;temp[i]=0;
            i++;
        }
        printf("enter the first number\n");
        scanf("%s",string1);
        printf("enter the second number\n");
        scanf("%s",string2);
        if(strlen(string1)>1000||strlen(string2)>1000)
        {
            printf("input is too long");//handles VERY LARGE NUMBERS
            continue;
        }

        if(string1[0]!='-')
        {
        negative1=0;
        for(i=1500-strlen(string1),j=0;i<1500;i++,j++)
        {
            num1[i]=string1[j]-48;
        }
        }
        else
        {
        negative1=1;
        for(i=1501-strlen(string1),j=1;i<1500;i++,j++)
        {
            num1[i]=string1[j]-48;
        }
        }
         if(string2[0]!='-')
        {
         negative2=0;
        for(i=1500-strlen(string2),j=0;i<1500;i++,j++)
        {
            num2[i]=string2[j]-48;
        }
        }
        else
        {
         negative2=1;
        for(i=1501-strlen(string2),j=1;i<1500;i++,j++)
        {
            num2[i]=string2[j]-48;
        }
        }
         if((negative1==1)&&(negative2==1))//handles negative inputs
            {
            subtract(num2,num1);
            }
            if((negative1==0)&&(negative2==1))
            {
                add(num1,num2);
            }
            if((negative1==1)&&(negative2==0))
            {
                printf("-");
            add(num2,num1);
            }
            if((negative1==0)&&(negative2==0))
                subtract(num1,num2);
        printresult();
        break;
        case 4:i=0;
            while(i<1500)
        {
            num1[i]=0;num2[i]=0;result[i]=0;temp[i]=0;
            i++;  
        }
        printf("enter the first number\n");
        scanf("%s",string1);
        printf("enter the second number\n");
        scanf("%s",string2);

        if(string1[0]!='-')//handles negative numbers
        {
        negative1=0;
        for(i=1500-strlen(string1),j=0;i<1500;i++,j++)
        {
            num1[i]=string1[j]-48;
        }
        }
        else
        {
        negative1=1;
        for(i=1501-strlen(string1),j=1;i<1500;i++,j++)
        {
            num1[i]=string1[j]-48;
        }
        }
         if(string2[0]!='-')
        {
         negative2=0;
        for(i=1500-strlen(string2),j=0;i<1500;i++,j++)
        {
            num2[i]=string2[j]-48;
        }
        }
        else
        {
         negative2=1;
        for(i=1501-strlen(string2),j=1;i<1500;i++,j++)
        {
            num2[i]=string2[j]-48;
        }
        }
            for(i=1499;i>=0;i--)
            {
                if(num2[i]!=0)
                    break;
                no_of_zeroes++;
            }
                if(no_of_zeroes==1500)
                {
                    printf("INVALID INPUT\n");
                    continue;
                }
               if(((negative1==1)&&(negative2==1))||((negative1==0)&&(negative2==0)))
             {
            divide(num1,num2);
            }
            else
            {
                printf("-");
                divide(num1,num2);
            }
            break;
        case 5:
            return 0;
            break;
        default:
            printf("please enter valid input\n");
            continue;
        }



    }
    }
