#include <unistd.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include<sys/wait.h>
using namespace std;
string replaceString(string tgt, string rep, string body);
int main()
{
	//Variable declarations
	string bodyText = "Anakin Skywalker is a young boy who meets Obi-Wan Kenobi and learns the ways of the Force (and to become a Jedi). Although Jedi are not allowed to get married, as an adult Anakin falls in love with Senator Padmé Amidala and they get married. Anakin later goes to the Dark Side and turns against Obi-Wan Kenobi and the rest of the Jedi. He then renames himself Darth Vader. Before he turned against his wife, Anakin had two children with Senator Amidala, Leia and Luke Skywalker, that he does not know about. Senator Amidala dies after giving birth to their twins. After birth, the twins are separated to prevent Vader and the Dark Side from finding and hurting the children. Obi-Wan Kenobi sends Luke to a planet called Tatooine to live with his Uncle Owen and Aunt Beru. \nLeia is raised by Senator Bail Organa of the planet Alderaan; she is called Princess Leia Organa. When they get older, Luke and Leia meet again. At first they don't know that they are brother and sister, but they eventually find out. They help fight the evil government, called the Galactic Empire. Luke also learns the ways of the Jedi from Obi-Wan Kenobi and Yoda. In the end, they defeat the Empire, with the help of the Rebellion, and Luke helps his father Anakin become good again. Unfortunately, Anakin dies. The galaxy is then saved for a while. \nThirty years later, however, the Empire rises again in the form of the First Order. However, the New Republic does not believe that it is a threat. Those who do believe form the Resistance, led by Leia. Luke has vanished, and Leia has married Han Solo. They had a child, named Ben, but Ben was corrupted by the First Order and is now called Kylo Ren. Rey, a desert scavenger, fights with Han against the First Order, but Kylo Ren kills his father. However, Rey still manages to gain a large defeat against the First Order with the help of the Resistance. Rey then finds Luke, who was searching for the first Jedi Temple and for more knowledge about the Jedi.";
	long childPID;
	string targetString;
	string replacement;
	bool running = true;
	//Output text to user
	cout << "Welcome to the word replacement program!\nHere is the text provided: \n\n" << bodyText;
	//Loop to prompt user for text. Will break if user enters !wq at either point
	while(running)
{
	cout << "\nPlease enter a word that you want to replace(!wq to quit): ";
	cin >> targetString;
	if(targetString == "!wq")
	{
		running = false;
		break;
	}
	cout << "Now please enter the word you want to replace it with (!wq to quit): ";
	cin >> replacement;
	if(replacement == "!wq")
	{
		running = false;
		break;	
	}	
	//Create child process
	childPID = fork();
	if (childPID ==0)
	{		
		//Child runs this. Set to false to end loop. function call to return a string and output
		//New string is output but original is not altered in any way.		
		running = false;
		string newStr = replaceString(targetString,replacement, bodyText);
		cout << newStr;
	}
	else if (childPID > 0)
	{
		//Parent runs this
		//Simply wait for child process to finish, then returns to top of loop
		wait(NULL);

	}
}
	exit(0);
}
string replaceString(string targetStr, string replacement, string body)
{
	//Var to track how many times it changed
	int num = 0;
	size_t targetPos = 0;
	while(num ==0)
	{
		//Search for word beginning at 0. if found, targetPos is set to that position. Do this until the end of the string
		while((targetPos = body.find(targetStr, targetPos)) != string::npos)
		{
			//Replace string at targetPos length of targetStr with replacement
			body.replace(targetPos, targetStr.length(),replacement);
			targetPos += replacement.length();
		 //Incremement targetPos by length of replacement as to not go over the same chars infinitely in situations where the replacement has same characters ie "af" replaced with "aft"
			num++;
		}
	cout << "Searching...\n";}//end of num while
	cout << "The word \"" << targetStr << "\" was replaced " << num << " times.\n\n";
	//Return altered text
	return body;
}
