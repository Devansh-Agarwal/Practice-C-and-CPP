#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/mman.h>

using namespace std; 
int main(int argc, char  *argv[])
{
	int fd; // shared memory file discriptor

	struct timeval *start, end; // structs to store the times 

	
	fd = shm_open("OS", O_CREAT | O_RDWR, 0666); // creating memory
	ftruncate(fd, 4096);
	start = (struct timeval *)mmap(0, 4096, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	pid_t pid;
	pid = fork();
	
	if(pid == 0)// child process
	{
		gettimeofday(start, NULL);
		execvp(argv[1],argv  +1 );
	}
	else if (pid > 0) // parent process
	{
		
		wait(NULL);
		gettimeofday(&end, NULL); 
		double time = (end.tv_usec - start->tv_usec)/1000000.0 +  (end.tv_sec - start->tv_sec); // calculate time elapsed 
		cout<< "Elapsed time: " <<time << endl;
		shm_unlink("OS"); // deleteing memory
	}
	else
	{
		cout << "Process creation failed\n";
		return 1 ;
	}

	return 0;
}
