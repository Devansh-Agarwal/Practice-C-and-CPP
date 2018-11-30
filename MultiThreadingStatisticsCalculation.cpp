#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <vector>
#include <cmath>
#include <algorithm> 
#include <sys/time.h>

using namespace std;
long double avg = 0, stdDev = 0, median = 0;
int size = 0; double temp = 0;
vector<double> numbers, numbers_temp;


// 3 threads are created which calculate one of the 3 statistical values
void *calAvg(void * param) // caluclate average 
{
	for(double a : numbers)
		avg += a;
	avg = (avg/(double)size);
}


void * calStdDev(void * param) // calculate standard deviation
{
	long double mean = 0;
	for(double a : numbers)
		mean += a;
	mean /= (double)size;
	for(double a : numbers)
	{
		stdDev += pow(a - mean, 2); 
	}
	if(size  == 1)
	{
		stdDev = 0;
		return NULL;
	}
	stdDev /= (size - 1);
	stdDev = sqrt(stdDev); 
}
void * calMedian(void * param) // calculate median
{	
	sort(numbers_temp.begin(), numbers_temp.end());
	if(size % 2 == 0)
		median = (numbers_temp[size/2] + numbers_temp[(int)(size/2) -1 ] )/ 2;
	else
		median = numbers_temp[size/2];
}
int main()
{
	// taking input
	cin >> size;
	numbers.reserve(size);
	numbers_temp.reserve(size);
	for(int i = 0; i < size; i ++)
	{
		cin>> temp;
		numbers.push_back(temp);
		numbers_temp.push_back(temp);
	}

	// creating threads and calling them and waiting for them
	pthread_t avgId, stdDevId, medianId;
	pthread_attr_t avgAttr, stdDevAttr, medianAttr;
	pthread_attr_init(&avgAttr);
	pthread_attr_init(&stdDevAttr);
	pthread_attr_init(&medianAttr);
	pthread_create(&avgId, &avgAttr,calAvg, NULL);
	pthread_create(&stdDevId, &stdDevAttr,calStdDev, NULL);
	pthread_create(&medianId, &medianAttr,calMedian, NULL);
	pthread_join(avgId, NULL);
	pthread_join(stdDevId, NULL);
	pthread_join(medianId, NULL);

	// 
	cout.precision(10);
	cout<< "The average value is "<<avg << endl;
	cout<< "The standard deviation value is "<<stdDev <<endl;
	cout<< "The median value is "<<median <<endl;

}	