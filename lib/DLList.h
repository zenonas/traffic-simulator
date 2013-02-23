/* Traffic Simulation System

Group Project 7CCSMGPR - Team B
Created: 16/2/2013
Updated: 16/2/2013
File: lib/DLList.h
Description: This is the header file describing the Doubly Linked List Class.

Copyright (c) King's College London

*/
#ifndef DLList_H
#define DLList_H

using namespace std;

template <class T> class DChain;
template <class T>

class DChainNode{
    friend class DChain<T>;
    private:
		T data;
		int SortValue;
		DChainNode<T> *flink;
		DChainNode<T> *blink;
};
template<class T>
class DChain{
   public:
	   DChain();
	   ~DChain();
	   bool IsEmpty();
	   int Length();
	   bool Find(int k, T& x);
	   DChain<T>& Delete(int k, T& x);
	   DChain<T>& Insert(int k, const T& x);
	   void Output();

   private:
	   DChainNode<T> *first; // pointer to first node
};

#endif