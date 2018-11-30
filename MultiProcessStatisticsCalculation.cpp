#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std; 
// 3 processes are  forked from the parent
int size = 0; double temp = 0;

vector<double> numbers, numbers_temp; // 2 vectors to store input

int main()
	{
	
	
	pid_t pid , pid1, pid2; 
	

	// taking input from command line using < filename
	cin >> size;
	numbers.reserve(size);
	

	for(int i = 0; i < size; i ++)
	{
		cin>> temp;
		numbers.push_back(temp);
		numbers_temp.push_back(temp);
	}


	int fd;
	fd = shm_open("OS", O_CREAT | O_RDWR, 0666); // creating memory
	ftruncate(fd, 4096);
	double* val = (double *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	val[0] = 0;
	val[1] = 0;
	val[2] = 0;
	val[3] = 0;
	if(val == NULL)
	{
		cout<<"Unable to create the shared memory" << endl;
		exit(0) ; 
	}
	pid = fork();
	
	if(pid > 0 )
		pid1 = fork();
	if(pid > 0)
		pid2 = fork();
	if(pid == 0) // mean
	{
		for(double a : numbers) 
			val[0]+= a;
		
		val[0] = (val[0]/(double)size);

	}
	if(pid1 == 0 && pid >0 && pid2 ==0  ) // standard deviation
	{
		if(val[3] < 0.000000001){
		double mean = 0;
		for(double a : numbers)
			mean += a;
		mean /= (double)size;
		for(double a : numbers)
		{
			val[1] += pow(a - mean, 2); 
		}
		if(size  == 1)
		{
			val[1] = 0;
		
		}
		else{
		val[1] /= (size - 1);
		val[1] = sqrt(val[1]);	
		}
			val[3]  == 4;

		}

	}
	 if ( pid1 >0 && pid2 == 0  ) // median
	{
		sort(numbers_temp.begin(), numbers_temp.end());
		if(size % 2 == 0)
			val[2] = (numbers_temp[size/2] + numbers_temp[(int)(size/2) -1 ] )/ 2;
		else
			val[2] = numbers_temp[size/2];

	}
	
	 if(pid > 0 && pid1 > 0 && pid2 > 0)
	{
		waitpid(pid,NULL,0);

		waitpid(pid1,NULL,0);
		waitpid(pid2,NULL,0);
		cout.precision(10);
		cout<< "The average value is "<< val[0] << endl;
		cout<< "The standard deviation value is "<<val[1] <<endl;
		cout<< "The median value is "<< val[2] <<endl;
	    shm_unlink("OS"); // deleteing memory
		
	}


}