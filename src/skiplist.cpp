#include <ctime>
#include <cstdlib>
#include <iostream>
#include <climits>
#include <cassert>
#include "skiplist.h"




//Creates the skiplist based on how the depth is. 
//Initializes front and rear guards based on the depth and connects
//them to each other and above below.
SkipList::SkipList(int depth)
{
	srand((unsigned int)time(NULL));
	this->depth = depth;
	this->rearGuards = new SNode*[depth];
	this->frontGuards = new SNode*[depth];
	for (int i = 0; i < depth; i++) {
		
		rearGuards[i] = new SNode(INT_MAX);
		frontGuards[i] = new SNode(INT_MIN);

		frontGuards[i]->next = rearGuards[i];
		rearGuards[i]->prev = frontGuards[i];
		rearGuards[i]->next = nullptr;
		frontGuards[i]->prev = nullptr;
	}
	for (int i = 0; i < depth - 1; i++) { 
		rearGuards[i]->upLevel = rearGuards[i + 1];
		frontGuards[i]->upLevel = frontGuards[i + 1];
		frontGuards[i + 1]->downLevel = frontGuards[i];
		rearGuards[i + 1]->downLevel = rearGuards[i];
	}

}
//Deletes all nodes inside the skiplist by going through one level at time.
//Then deletes the array of pointers themselves
SkipList::~SkipList()
{
	SNode *n;
	for (int i = 0; i < depth; i++) {
		//std::cout << "Level " << i << ":";
		n = frontGuards[i];
		while (n != nullptr) {
			if (n == rearGuards[i]) {
				//std::cout << n->data;
				SNode *copy = n;
				n = n->next;
				delete copy;
			}
			else {
			//	std::cout << n->data << ", ";
				SNode *copy = n;
				n = n->next;
				delete copy;
			}
		}
		//std::cout << std::endl;
	}
	delete[] frontGuards;
	delete[] rearGuards;
} 
//First sees if the data is in the skiplist and if it is, return 0,
//else adds it to the list in a sorted order of ascending
//throws coin and then based on results of toss
//creates more nodes to add to higher levels by doing same comparisons, but this time no check
//for equal data. Returns true if the item gets added to list, regardless of how many times
bool SkipList::Add(int data)
{
	SNode *frontptr = frontGuards[0]; 
	while (frontptr->next != nullptr) {
		frontptr = frontptr->next;
		if (frontptr->data == data) {
			return false;
		}
		if (frontptr->data > data) {
			length += 1;
			SNode * n = new SNode(data);
			SNode *connectNode = n; 
			addBefore(n, frontptr);
			bool goUp = alsoHigher();
			int level = 0;
			while(goUp && level + 1 < depth) { 
				frontptr = frontGuards[level + 1]; 
				while (frontptr->next != nullptr && frontptr != rearGuards[level +1]) { 
					frontptr = frontptr->next;
					if (frontptr->data > data ) {
						SNode *n2 = new SNode(data); 
						addBefore(n2, frontptr);
						connectNode->upLevel = n2; 
						n2->downLevel = connectNode;
						connectNode = n2; 
						break;
					}
				}
				level += 1;
				goUp = alsoHigher(); 
			}
			
			return true;
		}
	}
	return false;
}
//Starts at the top and goes through list like the contains method,
//but when the current pointer reaches the element, you change the list so
//the thing behind the item points to the next item and vice versa (connect nodes)
//then, you go down one level if there are more levels below, delete the node you were at,
//connect nodes again, then go down again if there are more levels below, else delete that
//node and return true. If you don't find the data on you run, return false.
bool SkipList::Remove(int data)
{
	if (length == 0) {
		return false;
	}
	SNode *current = frontGuards[depth - 1];
	while (current != nullptr) {
		if (current->next->data < data) {
			current = current->next;
		}
		else if (current->next->data == data) {
			length -= 1;
			current = current->next;
			current->prev->next = current->next; 
			current->next->prev = current->prev;
			while (current->downLevel != nullptr) {
				SNode *copy = current;
				current = current->downLevel;
				current->prev->next = current->next; 
				current->next->prev = current->prev;
				delete copy;
			}
			delete current;
			return true;
		}
		else {
			current = current->downLevel;
		}
	}
	return false;
}
//Checks to see if data is in list by starting from highest level
//and going on based on whether the node has a smaller value
//and down based on whether its larger, if you the value,
//return true, else at the end, it returns false.
bool SkipList::Contains(int value)
{
	int level = depth - 1;
	SNode *current = frontGuards[depth - 1];
	while (current->next != nullptr) {

		if (current->next->data < value) {
			current = current->next;

		}
		else if (current->next->data == value) {
			return true;
		}
		else if (current->next->data > value && current->downLevel != nullptr) {
			level -= 1;
			current = current->downLevel;
		}
		else {
			return false;
		}
	}
	return false;
}

int SkipList::getLength()
{
	return this->length;
}

//Connects new node to the nextNode, connects newNode prev to thenextNodes prev, then
//connects nexNode prev to newNode to fix the chain.
void SkipList::addBefore(SNode * newNode, SNode * nextNode)
{
	newNode->next = nextNode; 
	newNode->prev = nextNode->prev; 
	newNode->prev->next = newNode; 
	nextNode->prev = newNode;

}


//Coint toss simulations using the rand()

bool SkipList::alsoHigher() const
{
	if (rand() % 2 == 1) {
	
		return true;
	}
	return false;
}



//Friend functions which prints from the lowest level to the highest
//level.
std::ostream & operator<<(std::ostream & os, const SkipList & list)
{
	SkipList::SNode* n ;
	for (int i = list.depth-1; i >=0 ; i--) {
		std::cout << "Level " << i <<":";
		n = list.frontGuards[i];
		while (n != nullptr) {
			if (n == list.rearGuards[i]) {
				os << n->data;
				n = n->next;
			}
			else {
				os << n->data << ", ";
				n = n->next;
			}
		}
		os << std::endl;
	}
	return os;
}

