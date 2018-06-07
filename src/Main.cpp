#include <iostream>
#include <cassert>
#include "skiplist.h"
using namespace std;



//This tests for removing elements from the list.
void Test01() {
	SkipList t(2);
	
	for (int i = 0; i < 10; i++) {
		t.Add(i);
	}
	for (int i = 0; i < 5; i++) {
		t.Remove(i);
	}
	
	
	cout << t;
}
//List with different number of depth and adding elements 
//with order of ascending.
void Test02() {
	SkipList t(4);
	t.Add(5);
	t.Add(-1);
	t.Add(2);

	t.Add(99);
	t.Add(5);
	t.Add(1000);
	t.Add(-33);
	t.Add(5);

	cout << endl << t;
}
//Checks both contains and remove method work and 
//complemet each other.
void Test03() {
	SkipList t(3);
	for (int i = 0; i < 10; i++) {
		t.Add(i);
	}

	assert(t.Contains(3));
	assert(!t.Contains(99));
	assert(t.Remove(3));
	assert(!t.Contains(3));
	cout << endl << t;

}
void Test00() {
	SkipList t(1);
	cout << t;

}



int main() {
	Test03();
	cout << endl;
	Test01();
	cout << endl;
	Test00();
	cout << endl;
	cout << "Successfully compiled";
	

}
