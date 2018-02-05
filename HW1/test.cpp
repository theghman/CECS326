#include <iostream>
#include <stdlib.h>
using namespace std;
struct charStruct
{	//struct for charArray
	char * charArray[20];
	unsigned int intArray[20];
};
int f(int n); //Recursive function
void initChar(charStruct &ptr);
void initializeNum(charStruct &ptr);
void accessPointer();

int main()
{
	srand(time(NULL)); //Random seed
	int optionNum;
	charStruct charmander;//Single struct created
	initializeNum(charmander); //Initialize number of elements for struct intArray
	initChar(charmander);
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
				accessPointer();
			}
		else if (optionNum==2)
		{
			cout << "2";
		}
		else if (optionNum==3)
		{
			for (int i =0; i < 20;i++)
			cout <<charmander.intArray[i] <<endl;
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
    for (int i=0;i<21;i++)
    {
        ptr.intArray[i] = f(i); //assign a value based on each index in array
    }
}
int f(int n)
{
    if (n==21)
	{
	    return 0;
	}
	//Return 2700 if zero
	if (n == 0)
 	{
		return 2700;
	}
	else //Return 2 * f(n-1)
		return (2*f(n-1));

}
void initChar(charStruct &ptr)
{   
    char * holdchar;
    int SIZE;
	for (int i = 0; i <20; i++)//Doesn't work with 19+
	{
	    SIZE = ptr.intArray[i];
	    holdchar = new char[SIZE];
	    for (int j =0; j < SIZE; j++)
	    {
	        holdchar[j]='A' + rand()%26;
	    }
		ptr.charArray[i] = holdchar;
		delete[] holdchar;
	}
}
void accessPointer()
{
	int numChoice;
	cout << "Which pointer are you trying to access? (1-20)";
	cin >> numChoice;
	cout << "Accessing pointer....\n";
	cout << "1)Print first 10 chars in chosen array\n" <<"2)pDelete all chars associated with this pointer\n" <<"3)Return to main menu\n";
	cin >> numChoice;
}
