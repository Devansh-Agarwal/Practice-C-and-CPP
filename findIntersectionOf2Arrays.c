#include <stdio.h>
#include <stdlib.h>

int n, m;// declaring the sizes of the two arrays in global variables

void bSort(int * arr, int n)// sorts an array usig bubble sort
{
	int temp;// used for swapping elements
	
	for(int i= 0; i<n-1;i ++)
	{
		int swapped = 0;
		for(int j= 0 ; j<n-i-1;j ++)
		{
			if(arr[j]>arr[j+1])// if the next element is smaller than current element swap them
			{
				temp= arr[j+1];
				arr[j+1]=arr[j];
				arr[j]=temp;
				swapped ++;
			}
		}
		if(swapped == 0)// if number of swaps are 0 then the array is sorted
				break;
	}
}

// takes in two sorted arrays and finds there intersection
void printIntersection(int * arr1, int * arr2)
{
	int flag = 0 ; // used for checking the case when there are no intersection
	for(int i = 0; i < n; i++)//runs till the end of the 1st array is reached
	{
		for(int j = 0; j < m; j++)//runs till the end of the 2nd array is reached
		{
			//if the current element of arr2 is bigger than that of current element of arr1 no chance of 
			//finding that element as intersection the rest two conditions check for repeated values 
			if((arr2[j]> arr1[i]) ||((i< n-1)&& (arr1[i] == arr1[i+1]))) 
				break;
			if(arr1[i] == arr2[j])// if intersection found
			{
				if(flag++ == 0)// there is atleast 1 intersection
					printf("The intesecting elements are ::\n");
				printf("%d\n",arr1[i]);
				break;
			}
		}
	}
	if(flag == 0)// no common intersections
		printf("There are no intersecting elements\n");
}

void main()
{
	printf("Enter the size of the 1st array\n");
	scanf("%d",&n);
	printf("Enter the size of the 2nd array\n");
	scanf("%d",&m);
	
	// dynamically allocating memory for 2 arrays
	int * arr1 = (int *) malloc(sizeof(int)*n);
	int * arr2 = (int *) malloc(sizeof(int)*n);
	if(arr1 == NULL || arr2 == NULL)// if there is no memory to spare for array
	{
		printf("Memory Overflow\n");
		return;
	}

	// taking inputs of the 2 arrays
	printf("Enter elements of 1st array\n");
	for(int i = 0;  i < n; i++)
    {
    	printf("Enter element %d\n",(i+1));
    	scanf("%d",&arr1[i]);	
    }
    printf("Enter elements of 2nd array\n");	

    for(int i = 0;  i < m; i++)
    {
    	printf("Enter element %d\n",(i+1));
    	scanf("%d",&arr2[i]);	
    }

    // sorting both the arrays and then finding there intersections
    bSort(arr1, n);
    bSort(arr2, m);
    printIntersection(arr1, arr2);
}