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
#include <ctime>
#include <cstdlib>
#include "semaphore.h"
using namespace std;

enum {UVsemaphore}; 

void calculate(SEMAPHORE &, bool *, string);
void parent_cleanup(int arr[], SEMAPHORE &, int schmid);

int main(){
	int shmid = shmget(IPC_PRIVATE, sizeof(bool), PERMS);
	bool *shmBUF = (bool *)shmat(shmid, 0, SHM_RND);
	*shmBUF = true;

	pid_t child;

	SEMAPHORE sem(1); 
	sem.V(UVsemaphore); 
	sem.V(UVsemaphore);

	int arr[4];

	if ((arr[0] = fork())){//parent
		if((arr[1] = fork())){
			if((arr[2] = fork())){
				if((arr[3] = fork())){
					parent_cleanup(arr, sem, shmid);
				}else{//child D
					calculate(sem, shmBUF, "D");
				}
			}else{//child C
				calculate(sem, shmBUF, "C");
			}
		}else{//child B
			calculate(sem, shmBUF, "B");
		}
	}else{//child A
		calculate(sem, shmBUF, "A");
	}

    return 0;
}

void calculate(SEMAPHORE &sem, bool *shmBUF, string childLetter) {
	int randNum;

	bool v = *shmBUF;
	sem.P(UVsemaphore);
	srand(time(NULL));
	if(v){
		int V = 962094883;
		*shmBUF = false;

		do{
			randNum = rand() % 100000;
			cout << childLetter << " : " << randNum << " compare to " << V << endl;
		}while(randNum % V != 0 || randNum >= 100);
		cout << childLetter << " is done." << endl;
		*shmBUF = true;
	}else{
		int U = 827395609;

		do{
			randNum = rand() % 100000;
			cout << childLetter << " : " << randNum << " compare to " << U << endl;
		}while(randNum % U != 0 || randNum >= 100);
		cout << childLetter << " is done." << endl;
	}
	sem.V(UVsemaphore);	
} 

void parent_cleanup (int arr[], SEMAPHORE &sem, int shmid) {
	string choice = "";
	do{		
		cout << "Type '!wq' to quit. " << endl;
		cin >> choice;
	}while(choice.compare("!wq") != 0);

	cout << "Killing all children." << endl;
	for (int id = 0; id<4; id++){
		kill(arr[id],SIGTERM);
	}
	shmctl(shmid, IPC_RMID, NULL);
	cout << "Ending the parent.\nExiting..." << endl;
	sem.remove();
	exit(0);
} // parent_cleanup
