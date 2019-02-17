#include <iostream>
#include <string>
#include <limits>			//for numeric_limits

#include "Node.h"
#include "LinkedChar.h"

//Function Prototypes
int  menuChoice();
void menuChoiceSwitchDriver(const int&, LinkedChar&);
void clearInput();
void displayLength(const LinkedChar&);
void getIndexOfChar(const LinkedChar&);
void appendOriginalObject(LinkedChar&);
void isSubString(const LinkedChar&);

int main()
{
	char goAgain = 'n';

	std::string startingString;
	std::cout << "Please enter a string to begin: ";
	std::getline(std::cin, startingString);
	LinkedChar originalLinkedList(startingString);

	do{
		int userChoice = menuChoice();
		menuChoiceSwitchDriver(userChoice, originalLinkedList);
		if (userChoice != 5)
		{
			std::cout << "\nWould you like to do more (y/n)? : ";
			std::cin  >> goAgain;
		} //end if
	}while (goAgain == 'y' || goAgain== 'Y'); //end do-while

	std::cout << "Goodbye!";
	return 0;
}

int menuChoice()
{
	int menuChoice;
	bool correctChoice;

	std::cout << "\nChoose from the following options:\n";
	std::cout << "\t1. Display the number of characters in your string.\n"
			  << "\t2. Find the index of a character in your string.\n"
			  << "\t3. Append to your current string.\n"
			  << "\t4. Check to see if there's a matching substring.\n"
			  << "\t5. Exit the menu (will prompt you to go again).\n";
	do{
	std::cout << "What is your choice?: ";

	if (std::cin  >> menuChoice && (menuChoice >= 1 && menuChoice <= 5))
		correctChoice = true;
	else
	{
		clearInput();
		std::cout << "**Incorrect input. Please enter 1-6 for menu options**\n";
		correctChoice = false;

	}//end if
	}while (!correctChoice);
	return menuChoice;
}

//Clears input buffer. std::getline() usually leaves '\n' lines, this makes sure
//that if something goes wrong, the buffer is cleared out
void clearInput()
{
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

//Main driver for switch case. Will be called in main and passes through
//the original object to me displayed, manipulated, searched, or deleted.
void menuChoiceSwitchDriver(const int& userChoice, LinkedChar& object)
{
	clearInput();								//clear buffer from previous input
	switch(userChoice)
	{
		case 1:
			displayLength(object);
			break;
		case 2:
			getIndexOfChar(object);
			break;
		case 3:
			appendOriginalObject(object);
			break;
		case 4:
			isSubString(object);
			break;
		case 5:
			std::cout << "Leaving menu...\n";
			break;
		default:
			std::cout << "Error: please enter a proper option.\n";
	}
}//end menuChoiceSwitchDriver()

void displayLength(const LinkedChar& object)
{
	std::cout << "The string has " << object.length() << " characters.\n";
} //end displayLength()

void getIndexOfChar(const LinkedChar& object)
{
	std::string characterSearch;
	bool successfulInput = true;

	do{
		std::cout << "Current string: '";
		object.displayLinkedChar();
		std::cout << "'.\nChoose a character to find its index, if the character is found: ";
		std::getline(std::cin, characterSearch);
		if (characterSearch.length() <= 0 || characterSearch.length() > 1)
		{
			std::cout << "Incorrect input. Please input a single proper character "
			          << "(a-z, 0-9, symbol).\n";
			successfulInput = false;
		}
		else
		{
			successfulInput = true;
			int index = object.index(characterSearch[0]);
			if (index == -1)
				std::cout << "Character not found within string...\n";
			else
				std::cout << "Character first found at index: " << index << "\n";
		}//end if
	}while (!successfulInput); //end do-while
} //end getIndexofChar()

void appendOriginalObject(LinkedChar& object)
{
	std::string appendingString;

	std::cout << "Please enter a string to append "
			  << "(note, this permenately changes the original object): ";
	std::getline(std::cin, appendingString);
	std::cout << "\nAppending string to orignal string...\n";
	LinkedChar appendingObject(appendingString);
	object.append(appendingString);
	std::cout << "Here's the original string, appended: \n\t";
	object.displayLinkedChar();
	std::cout << "\n";

} //end appendOriginalObject()

void isSubString(const LinkedChar& object)
{
	std::string subString;
	std::cout << "Please enter a string in to see whether or not "
			  << "it exists as a substring: ";
	std::getline(std::cin, subString);
    LinkedChar subChain(subString);
	if (object.submatch(subChain))
	{
		std::cout << "'" << subString << "' exists as a substring in '";
		object.displayLinkedChar();
		std::cout << "'\n";
	}
	else
	{
		std::cout << "'" << subString << "' does not exist as a substring in '";
		object.displayLinkedChar();
		std::cout << "'\n";
	}//end if
	std::cout << std::endl;
}//end isSubString()
