/*   @File: Node.h
	Author: Jacob Christian
	Professor: Michael Miller
	Class: COSC-2436-004 Mon/Wed
*/

#ifndef NODE
#define NODE

class Node
{
private:
	char character;
	Node* next;
public:
	Node() : next(nullptr) {}						  								//default constructor
	Node(const char& aChar) : character(aChar), next(nullptr) {} 					//paramiterized constructor
	Node(const char& aChar, Node* nextPtr) : character(aChar), next(nextPtr) {}		//paramiterized constructor
	//mutators
	void setChar(const char& newchar)
		{ this->character = newchar;}
	void setNext(Node* nextPtr)
		{ this->next = nextPtr; }
	//accessors
	char getChar() const
		{ return character; }
	Node* getNext() const
		{ return next;}
};

#endif //NODE


