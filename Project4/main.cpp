#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "semaphore.h"

using namespace std;
//Constants given in prompt
const int U = 827395609;
const int V = 962094883;
const int BUFFSIZE = 1;
enum{SEMUV};

void integerCheck(SEMAPHORE & sem, bool *);
void factorCheck(int factorOf);
void parent_cleanup (SEMAPHORE &sem, int shmid, int childrenID[]);
int main()
{
	int shmid;
	bool *shmBUF;
	string uInput;
	int childrenID[4];

	shmid = shmget(IPC_PRIVATE, BUFFSIZE*sizeof(char), PERMS);
	shmBUF = (bool *)shmat(shmid, 0, SHM_RND); //Boolean to track U
	*shmBUF = true;
	//Sempahore Initialization
	SEMAPHORE sem(1);
	sem.V(SEMUV);//Increment by 1
	sem.V(SEMUV);//Increment by 1

	//Creating for child processes and assigning them to an array
	if((childrenID[0]=fork()))
	{//Parent
		if((childrenID[1]=fork()))
		{//Parent
				if((childrenID[2]=fork()))
				{//Parent
					if((childrenID[3]=fork()))
					{//Parent
						parent_cleanup(sem, shmid, childrenID); //Parent calls
					}
					else
					{//Child 4 process
						integerCheck(sem,shmBUF);
					}
				}
				else
				{//Child 3 process
					integerCheck(sem,shmBUF);
				}
		}
		else
		{//Child 2 process
			integerCheck(sem,shmBUF);
		}
	}
	else
	{//Child 1 process
		integerCheck(sem,shmBUF);
	}
	
}
/*
This function will serve as a critical section with use of semaphore. boolean will check first if any integer is working on U var, else work on V var in factorCheck func. Semaphore will be decremented so that max processes that can run CS is 2
@params
sem - semaphore to use
shmBUF - boolean to check if U var is available
*/
void integerCheck(SEMAPHORE & sem, bool *shmBUF)
{
	//Beginning of the critical section protected by semaphore
	bool computeU = *shmBUF; //Check if U var is available
	sem.P(SEMUV);
	if (computeU)
	{
		//If True, pass U value to factorCheck to calculate
		*shmBUF = false;//Mark U as inaccessible
		factorCheck(U);
		*shmBUF = true;//Once it is complete, mark U accessible for other processes
	}
	else //If U is no available, pass V
	{
		factorCheck(V);
	}
	sem.V(SEMUV);
	//End of CS
}
/*
This function will generate a random integer and check if it is divisible by U or V(per prompt)
@params
factorOf - value of U or V as determined in integerCheck()
*/
void factorCheck(int factorOf)
{
	//factorOf will be U or V value determined in integerCheck function
	srand(time(NULL)); //Prepare seed for random number
	int randomNum = 101;	
	//If randomNum is less than 100, while loop ends
	
	while(randomNum>100)
	{
		randomNum = rand();//Generate random number
		cout << "PID "<<getpid() << " checking" << factorOf << "%" << randomNum <<"=" << randomNum%factorOf << "(!wq to quit all processes)\n";
		if (randomNum%factorOf==0)
		break;//If U or V is a factor of the random number, break from the loop;
	}
	cout << "Done";
}
/*
This process will kill all process in the array and do the necessary cleanup
@params
sem - semaphore used
shmid- id
childrenID - array storing child processes
*/
void parent_cleanup (SEMAPHORE &sem, int shmid, int childrenID[]) {
	string command;
	while(command != "!wq")
	{
		cin >> command;//Run until user enters !wq to quit
	}
	for (int i = 0; i <4; i++)
	{
		kill(childrenID[i], SIGTERM);//Kill each process in array
	}
	cout << "Killing children...\n";
	shmctl(shmid, IPC_RMID, NULL);
	cout <<"Program is now ending.\n";
	sem.remove();
	exit(0);
}
