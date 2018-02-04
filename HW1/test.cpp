#include <iostream>
#include <stdlib.h>
using namespace std;
struct charStruct
{	//struct for charArray
	char ** charArray[20];
	int intArray[20];
};
void initChar(charStruct *ptr);
void accessPointer();
//Recursive function
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
int main()
{
	srand(time(NULL)); //Random seed
	int optionNum;
	charStruct charmander;//Single struct created
	do{
		cout << "Welcome! Please choose an option:\n1) Access a pointer\n";
		cout << "2) List deallocated memory(index)\n3) Deallocate all memory\n4) Exit\n";
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
			cout << "3";
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

void accessPointer()
{
	int numChoice;
	cout << "Accessing pointer....\n";
	cout << "1)Print first 10 chars in chosen array\n"
<<"2)pDelete all chars associated with this pointer\n" <<"3)Return to main menu\n";
	cin >> numChoice;
}

void initChar(charStruct *ptr)
{
	for (int i =0;i <20;i++)
	
	for (int i = 0; i <20; i++)
	{
		//ptr[i]= 'A' + rand()%26;
	}
	for (int i = 0; i <20; i++)
	{
		//cout << ptr[i];
	}
}
