#pragma once
#include <iostream>


class SkipList
{

private:
	class SNode {
	public: 
		//This is the data the node will carry
		int data;
		//Pointer to the next node.
		SNode *next = nullptr;
		//Points to the previous node
		SNode *prev = nullptr;
		//Link to the above level
		SNode *upLevel = nullptr;
		//Link to below level
		SNode *downLevel = nullptr;
		SNode(int data) {
			this->data = data;
		}
		//default constructor
		SNode() {}
	};

	//coin toss run for moving nodes up the levels of skip list.
	bool alsoHigher() const;

	int length =0;

	//The brackets for the skiplist that contain all elements 
	//that you add.
	SNode **rearGuards;

	SNode **frontGuards;

	//Level of skip list
	int depth;

	//Puts the newNode before the next node
	void addBefore(SNode *newNode, SNode *nextNode);

public:
	//Basic constructor, starts with depth 1.
	SkipList(int depth=1);

	//Basic destructor, allows for modifications in deletions (delete all
	//elements in the skiplist
	virtual ~SkipList();

	//Adds a node with this data to the skip list
	bool Add(int data);

	//Removes the node with this data from the skip list
	bool Remove(int data);

	//Checks whether the node with this data exists in the skip list.
	bool Contains(int value);

	//Method that returns how many nodes are within the skiplist
	int getLength();

	//Functions that print out all elements in the skiplist,
	//low level to high level
	friend std::ostream &operator<<(std::ostream &os, const SkipList &list);
};

