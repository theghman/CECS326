#include <iostream>
#include <stdlib.h>
using namespace std;
struct charStruct
{	//struct for charArray
	char ** charPointer;
	int * intArray;
};
int f(int n); //Recursive function
void initializeChar(charStruct &ptr, int i);//Function to initialize char elements
void initializeNum(charStruct &ptr);//Function to initialize integer array
void accessPointer(charStruct &ptr);//Submenu to manipulate pointer
void deallocPointer(charStruct &ptr, int i);//Function to deallocate memory
void listDealloc(charStruct &ptr);//Function to list all empty chars
int main()
{
	charStruct charmander; //create struct
	initializeNum(charmander);//Initialize integer array elements
	charmander.charPointer=(char**)malloc(20*sizeof(char*));//Initialize 20 char pointers
	for(int i=0;i<20;i++)
	{
		initializeChar(charmander,i);//Loop to initialize char elements 
	}
	int optionNum;
	do{
		cout << "Welcome! Please choose an option:\n1) Access a pointer\n" << "2) List deallocated memory(index)\n3) Deallocate all memory\n4) Exit\n";
		cin >> optionNum;
		if(cin.fail()) //Check to see if input is a number
		{	
			cin.clear(); //Clear cin
			optionNum=0;//set to 0
		}
		if (optionNum==1)
			{
				accessPointer(charmander);//Pass struct to function
			}
		else if (optionNum==2)
		{
			listDealloc(charmander);
		}
		else if (optionNum==3)
		{
			for(int i=0; i < 20; i++)
			{
				deallocPointer(charmander,i);
			}
		}
		else if (optionNum==4)
		{
			cout << "Goodbye!\n";
		}
		else
		{	cout << "invalid entry";
			cin.ignore();//Check if user enters any other value or not an int
		}
	}while (optionNum !=4);
	for(int i =0; i < 20;i++)
	{
		deallocPointer(charmander,i);
	}
return 0;
}

void initializeNum(charStruct &ptr)
{
    ptr.intArray =(int*)malloc(20*sizeof(int)); //allocate 20 block of memory
    for (int i =0; i < 20; i ++)
    {
        ptr.intArray[i]=f(i);//Recursive function call
    }
}
int f(int n)
{
	//Return 2700 if zero
	if (n == 0)
 	{
		return 2700;
	}
	else //Return 2 * f(n-1)
		return (2*f(n-1));
}
void initializeChar(charStruct &ptr, int i)
{
   srand(time(NULL)); //Random number generation 
       ptr.charPointer[i]=(char*)malloc(ptr.intArray[i]*sizeof(char));//Allocate [array] number of char space
       for(int j = 0;j<ptr.intArray[i]; j++)
       {
           char randomLetter = 'A' + rand()%26;//generate a random capital letter
           ptr.charPointer[i][j]=randomLetter;//Assign to char array
       }
}
void accessPointer(charStruct &ptr)
{
    int pointChoice;
	int numChoice;
	do{
	cout << "Which pointer are you trying to access?";
	cin >> pointChoice;
	cout << "Accessing pointer....\n";
	cout << "1) Print first 10 chars in chosen array\n" <<"2) Delete all chars associated with this pointer\n" <<"3) Return to main menu\n";
	cin >> numChoice;
	cin.get();
	if(numChoice ==1)
	{
		if (ptr.charPointer[pointChoice][0]=='\0')
		{
			cout << "That index is empty! Reinitializing...\n";
			initializeChar(ptr, pointChoice);
		}
		for (int i =0; i < 10;i++)
		{
	    		cout << ptr.charPointer[pointChoice][i];
		}
		cout << endl;
	}
	else if (numChoice ==2)
	{
		deallocPointer(ptr, pointChoice);//call to deallocate memory 
	}
	}while(numChoice!=3);
}
void deallocPointer(charStruct &ptr, int i)
{
	free(ptr.charPointer[i]);//deallocate memory
	ptr.charPointer[i]=(char*)malloc(ptr.intArray[i]*sizeof(char));//Create memory block
	ptr.charPointer[i][0]='\0';//Reinitialize memory and set to NULL
}
void listDealloc(charStruct &ptr)
{
	cout << "Indexes with deallocated memory\n";
	for (int i =0; i < 20;i++)
	{
		if(ptr.charPointer[i][0]=='\0')
		{
			cout <<i << endl;//If character is null, output index where it is NULL
		}
	}
	
}


