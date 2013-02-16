/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: lib/DLList.cc
Description: The implementation file for the Doubly Linked List class

Copyright (c) King's College London

*/

#include <iostream>
#include "DLList.h"
#include "xcept.h"
using namespace std;

template<class T>
DChain<T>::DChain()
{
// Chain constructor. Delete all nodes in chain.
	first = 0;
}

template<class T>
DChain<T>::~DChain()
{
// Chain destructor. Delete all nodes in chain.
   DChainNode<T> *next; // next node
   while (first){
   next = first->flink;
   delete first;
   first = next;
   }
}

// Length, Find, Search are similar to the definition of corresponding
// methods in Chain class (Use flink instead of link)

template<class T>
bool DChain<T>::IsEmpty(){
	return first == 0; 
}

template<class T>
int DChain<T>::Length(){
	int count = 0;
	DChainNode<T> *p = first;
	while(!p || !p->flink) {
		p = p->flink;
		count++;
	}
	return count;
}

template<class T>
bool DChain<T>::Find(int k, T& x){
	// Set x to the k'th element and delete it.
	// Throw OutOfBounds exception if no k'th element.
	
	if (k < 1 || !first)	throw OutOfBounds();

	// p will eventually point to k'th node
	DChainNode<T> *p = first;

	// move p to k'th & remove from chain
	if (k == 1)
		first = p->flink;

	else { 

		for (int index = 1; index < k-1 && q; index++)
			p = p->flink;
		if (!p || !p->flink) return false; //no k element	
	}

	// save k'th element
	x = p->data;

	//Return true if k is found
	return true;
}


template<class T>
int DChain<T>::Search(T& x){
	// Search for the element x and return it's position.
	for(int k=1; k<Length(); k++) {
		if(Find(k,x)) return k;
	}
	return -1;
}

template<class T>
DChain<T>& DChain<T>::Insert(int k, const T& x){
   
   // Insert x after the k'th element.
   // Throw OutOfBounds exception if no k'th element.


   	// Pass NoMem exception if inadequate space.
	if (k < 0)
		throw OutOfBounds();

	// p will eventually point to k'th node
	DChainNode<T> *p = first;

	for (int index = 1; index < k && p; index++)
						p = p->flink; // move p to k'th

	if (k > 0 && !p)	throw OutOfBounds(); // no k'th

	// insert
	if (k) {
		DChainNode<T> *node= new DChainNode<T>;
		node->data = x;
		node->flink = p->flink;
		node->blink = p;
		p->flink=node;
		/* Put your code here */

	}
	else {
		DChainNode<T> *node= new DChainNode<T>;
		node->data = x;
		node->flink = first;
		node->blink = NULL;
		first = node;
		/* Put your code here */
	}

	//return the modified list
	return *this;

}

template<class T>
DChain<T>& DChain<T>::Delete(int k, T& x){
	// Set x to the k'th element and delete it.
	// Throw OutOfBounds exception if no k'th element.
	
	if (k < 1 || !first)	throw OutOfBounds();

	// p will eventually point to k'th node
	DChainNode<T> *p = first;

	// move p to k'th & remove from chain
	if (k == 1)
		first = p->flink;
	
	else { 
		DChainNode<T> *q = first;
		for (int index = 1; index < k-1 && q; index++)
			q = q->flink;
		if (!q || !q->flink) throw "OutOfBounds exception!";//no k
		p = q->flink;
		q->flink = p->flink;
		q->blink = q;
		p->blink = q;

	
	}

	// save k'th element and free node p
	x = p->data;
	delete p;

	//Return the modified list
	return *this;
}

template<class T>
void DChain<T>::Output()
{// Insert the chain elements into the stream out.
   DChainNode<T> *current;
   for (current = first; current;
                         current = current->flink)
      cout << current->data << "  ";
}


