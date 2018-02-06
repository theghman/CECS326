#include <iostream>
#include <stdlib.h>
using namespace std;
struct charStruct
{	//struct for charArray
	char ** charPointer;
	int * intArray;
};
int f(int n); //Recursive function
void initializeChar(charStruct &ptr);
void initializeNum(charStruct &ptr);
void accessPointer(charStruct &ptr);

int main()
{
    charStruct charmander; //create struct
    initializeNum(charmander);//Initialize array
    initializeChar(charmander);
    int optionNum;
	do{
		cout << "Welcome! Please choose an option:\n1) Access a pointer\n" << "2) List deallocated memory(index)\n3) Deallocate all memory\n4) Exit\n";
		cin >> optionNum;
		if(cin.fail()) //Check to see if input is a number
		{	
			cin.clear(); //Clear cin
			optionNum=0;
		}
		if (optionNum==1)
			{
				accessPointer(charmander);
			}
		else if (optionNum==2)
		{
			cout << "2";
		}
		else if (optionNum==3)
		{
			for (int i =0; i < 20;i++)
			{
			    
			}
		}
		else if (optionNum==4)
		{
			cout << "Goodbye!";
		}
		else
		{	cout << "invalid entry";
			cin.ignore();
		}
	}while (optionNum !=4);
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
void initializeChar(charStruct &ptr)
{
   srand(time(NULL)); //Random number generation 
   ptr.charPointer=(char**)malloc(20*sizeof(char*));//Initialize 20 char pointers
   for (int i = 0; i < 20; i++)
   {
       ptr.charPointer[i]=(char*)malloc(ptr.intArray[i]*sizeof(char));//Allocate [array] number of char space
       for(int j = 0;j<ptr.intArray[i]; j++)
       {
           char randomLetter = 'A' + rand()%26;
           ptr.charPointer[i][j]=randomLetter;
       }
   }
}
void accessPointer(charStruct &ptr)
{
    int pointChoice;
	int numChoice;
	cout << "Which pointer are you trying to access?";
	cin >> pointChoice;
	
	cout << "Accessing pointer....\n";
	cout << "1)Print first 10 chars in chosen array\n" <<"2)pDelete all chars associated with this pointer\n" <<"3)Return to main menu\n";
	cin >> numChoice;
	for (int i =0; i < 10;i++)
	{
	    cout << ptr.charPointer[numChoice][i] <<endl;
	}
}




