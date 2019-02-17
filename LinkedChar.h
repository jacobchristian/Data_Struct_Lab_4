/*   @File: Node.h
	Author: Jacob Christian
	Professor: Michael Miller
	Class: COSC-2436-004 Mon/Wed
*/

#ifndef LINKED_CHAR_
#define LINKED_CHAR_

#include "Node.h"
#include <iostream>
#include <string>

class LinkedChar
{
private:
	Node* headPtr;
	int itemCount = 0;
	void convertStringToCharList(const std::string&);

public:
	LinkedChar();
	LinkedChar(const std::string& stringToConvert);
	int length() const;
	int index(char characterSearch) const;
	void append(const LinkedChar& appendingLink);
	bool submatch(const LinkedChar& lc) const;
	Node* getHeadPtr() const;
	void displayLinkedChar() const;
};


/****************************************************
*                  IMPLEMENTATIONS                  *
****************************************************/
//default constructor
LinkedChar::LinkedChar() : headPtr(nullptr) {}

//convert constructor (automatically creates linked list)
LinkedChar::LinkedChar(const std::string& stringToConvert) : headPtr(nullptr)
	{ convertStringToCharList(stringToConvert); }


//returns a specific index of a node, much like it would be with an array/vector
int LinkedChar::index(char characterSearch) const
{
	int indexPosition = -1;										//Set index to -1 (meaning not found)
	int currentIndex = 0;										//Current Index set to first Node (like array)
	bool isFound = false;										//Set bool flag to false
	Node* currentPtr = headPtr;									//Store local headPtr into a temporary object

	while ( currentPtr != nullptr && !isFound)					//While not on the last node and search flag->false
	{
		if (currentPtr->getChar() == characterSearch)			//If the current node's character matches
		{
			indexPosition = currentIndex;						//Set the index to the current position
			isFound = true;										//Set search flag->true
		}
		else
		{
			currentPtr = currentPtr->getNext();					//Iterate through loop
			currentIndex++;										//Increment Index number
		}//end if

	} //end while
	return indexPosition;										//Return index (-1 if not found)
}

//appends a second LinkedChar object this local LinkChar object
void LinkedChar::append(const LinkedChar& appendingLink)
{
	Node* appendingPtr = appendingLink.getHeadPtr(); 			//store outside headPtr into temporary object
	Node* originalPtr = headPtr;								//store local headPtr into temporary object
	while (originalPtr->getNext()!= nullptr)					//Iterate through until we get to the second to last node
	{
		originalPtr = originalPtr->getNext();
	} //end while

	while (appendingPtr != nullptr)								//while referenced object's pointer is not the last node
	{
		Node* newNodePtr = new Node(appendingPtr->getChar());	//set a new object equal to the reference object's current char
		originalPtr->setNext(newNodePtr);						//set local object's next to the new node created
		originalPtr = originalPtr->getNext();					//set local object's pointer to the newly appointed node
		itemCount++;											//increment total number of nodes
		appendingPtr = appendingPtr->getNext();					//set the referenced object's next to the next node until nullptr

	} //end while
}

//Iterates through this LinkedChar object and searches for matching
//characters. If found, return true, else, return false
bool LinkedChar::submatch(const LinkedChar& linkToFind) const
{
	Node* subMatchPtr = linkToFind.getHeadPtr();				//store outside headPtr into temporary object
	Node* localPtr = headPtr;						//store local headPtr into temporary object
	Node* confirmSearchNode = headPtr;                                    	//store local headPtr to confirm match
	int correctCharacters = 0;				//keep track of correct number of characters for match

	while(localPtr->getNext() != nullptr) 						//Loop through local object
	{
	    confirmSearchNode = localPtr;						//Set confirm to current local node
		while ((subMatchPtr->getChar() == confirmSearchNode->getChar()) && (confirmSearchNode != nullptr))	
		{									//If the characters of both objects match
			correctCharacters++;                                //Increment correctCharacters by 1
			subMatchPtr = subMatchPtr->getNext();		    //Get the next node to check for the next characters
			confirmSearchNode = confirmSearchNode->getNext();   //Move through the local nodes
			if(correctCharacters == linkToFind.length())	    //equal number of nodes that match->found. return true
				return true;

		} //end while

		correctCharacters = 0;					    //Out of loop. Not found. Reset correctCharacters to 0.
		subMatchPtr = linkToFind.getHeadPtr();			    //Reset the outside object back to the head
		localPtr = localPtr->getNext();				    //Move to the next node to continue while loop
	}//end while
	return false;							    //If 1st while loop exits->not found. return false
} //end submatch()

//Function that converts a string to a linked list of character nodes
void LinkedChar::convertStringToCharList(const std::string& stringToConvert)
{
	for ( unsigned int index = stringToConvert.length(); index-- !=0;)
	{															//Iterate through string backwards
		Node* nextNodePtr = new Node();							//Create a new node object
		nextNodePtr->setChar(stringToConvert[index]);			//Set new node character to character indexed in string
		nextNodePtr->setNext(headPtr);							//Set new node's next to headPtr's address
		headPtr = nextNodePtr;									//Set headPtr's address to the new object
		itemCount++;											//Increment the number of nodes by 1
	}//end for
} //end convertStringToCharList();


//Display's the local object's nodes one by one out to console window
void LinkedChar::displayLinkedChar() const
{
	Node* currentPtr = headPtr;									//Create temporary node object, set to headPtr
	if (currentPtr == nullptr)									//If no objects, display message
		std::cout << "No characters to display.";
	else{
		while (currentPtr != nullptr) {							//Loop through nodes until it reaches the last node
			std::cout << currentPtr->getChar();					//Display the character stored in node
			currentPtr = currentPtr->getNext();					//Iterate through to the next node
		} //end while
	} //end if
}//end displayLinkedChar()

//returns the head of the object
Node* LinkedChar::getHeadPtr() const
	{return headPtr;}

//returns the number of nodes in our object
int LinkedChar::length() const
	{ return itemCount; }

#endif //LINKED_CHAR_

/*
//Iterates through this LinkedChar object and searches for matching
//characters. If found, return true, else, return false
bool LinkedChar::submatch(const LinkedChar& linkToFind) const
{
	Node* subMatchPtr = linkToFind.getHeadPtr();				//store outside headPtr into temporary object
	Node* localPtr = headPtr;									//store local headPtr into temporary object
	int correctCharacters = 0;									//keep track of correct number of characters for match

	while(localPtr->getNext() != nullptr) 						//Loop through local object
	{
		while (subMatchPtr->getChar() == localPtr->getChar())	//If the characters of both objects match
		{
			correctCharacters++;								//Increment correctCharacters by 1
			subMatchPtr = subMatchPtr->getNext();				//Get the next node to check for the next characters
			localPtr = localPtr->getNext();						//Move through the outside's nodes

			if(correctCharacters == linkToFind.length())		//equal number of nodes that match->found. return true
				return true;

		} //end while

		correctCharacters = 0;									//Out of loop. Not found. Reset correctCharacters to 0.
		subMatchPtr = linkToFind.getHeadPtr();					//Reset the outside object back to the head
		localPtr = localPtr->getNext();							//Move to the next node to continue while loop
	}//end while

	return false;												//If 1st while loop exits->not found. return false
} //end submatch()
*/
