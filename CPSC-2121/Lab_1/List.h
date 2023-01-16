/*
 * Name: Nikolaus Zampetopoulos
 * Date Submitted: 9/12/2022
 * Lab Section: 001
 * Assignment Name: Lab 1: Linked List Based Stacks and Queues
 */

#pragma once

#include <iostream>
#include <string>
#include "Node.h"
using namespace std;

//This class represents a linked list of node objects
//Do not modify anything in the class interface
template <class T>
class List{

	private:
		Node<T> * start; //pointer to the first node in this list
		int mySize;	//size (or length) of this list

	public:
		List();
		~List();
		int size();
		bool empty();
		void insertStart(T);
		void insertEnd(T);
		void insertAt(T, int);
		void removeStart();
		void removeEnd();
		void removeAt(int);
		T getFirst();
		T getLast();
		T getAt(int);
		int find(T);

		//Print the name and this list's size and values to stdout
		//This function is already implemented (no need to change it)
		void print(string name){
			cout << name << ": ";
			cout << "size = " << size();
			cout << ", values = ";
			Node<T> * iterator = start;
			while(iterator != nullptr){
				cout << iterator->value << ' ';
				iterator = iterator->next;
			}
			cout << endl;
		}

}; //end of class interface (you may modify the code below)

//Implement all of the functions below
//Construct an empty list by initializig this list's instance variables
template <class T>
List<T>::List(){
	start = nullptr;
	mySize = 0;
}

//Destroy all nodes in this list to prevent memory leaks
template <class T>
List<T>::~List(){
	Node<T> * iterator = start;
	while (iterator) {
		Node<T> * currentNodeptr = iterator;
		iterator = iterator->next;
		
		delete currentNodeptr;
	}
}

//Return the size of this list
template <class T>
int List<T>::size(){
	return mySize;
}

//Return true if this list is empty
//Otherwise, return false
template <class T>
bool List<T>::empty(){
	return !mySize;
}

//Create a new node with value, and insert that new node
//into this list at start
template <class T>
void List<T>::insertStart(T value){
	Node<T> * newNodeptr = new Node<T>(value);
	newNodeptr->next = start;
	start = newNodeptr;

	mySize++;
}

//Create a new node with value, and insert that new node
//into this list at end
template <class T>
void List<T>::insertEnd(T value){
	if (!start) {
		start = new Node<T>(value);
	} else {
		Node<T> * lastNodeptr = start;
		while (lastNodeptr->next) lastNodeptr = lastNodeptr->next;

		lastNodeptr->next = new Node<T>(value);
	}

	mySize++;
}

//Create a new node with value <value>, and insert that new node at position j
template <class T>
void List<T>::insertAt(T value, int j){
	if (!start || j <= 0) {
		Node<T> * oldStart = start;
		start = new Node<T>(value);
		start->next = oldStart;
	} else {
		Node<T> * nodeBeforeptr = start;
		for (int i = 0; i < j - 1 && nodeBeforeptr->next; i++) nodeBeforeptr = nodeBeforeptr->next;

		Node<T> * newNodeptr = new Node<T>(value);
		newNodeptr->next = nodeBeforeptr->next;
		nodeBeforeptr->next = newNodeptr;
	}

	mySize++;
}

//Remove node at start
//Make no other changes to list
template <class T>
void List<T>::removeStart(){
	if (start) {
		Node<T> * newStartptr = start->next;
		delete start;
		start = newStartptr;

		mySize--;
	}
}

//Remove node at end
//Make no other changes to list
template <class T>
void List<T>::removeEnd(){
	if (start) {
		if (!start->next) {
			delete start;
			start = nullptr;
		} else {
			Node<T> * secondLastNodeptr = start;

			while (secondLastNodeptr->next->next) secondLastNodeptr = secondLastNodeptr->next;

			delete secondLastNodeptr->next;
			secondLastNodeptr->next = nullptr;
		}

		mySize--;
	}
}

//Remove node at position j
//Make no other changes to list
template <class T>
void List<T>::removeAt(int j){
	if (start) {
		if (j <= 0 || !start->next) {
			Node<T> * oldStart = start;
			start = start->next;
			delete oldStart;
		} else {
			Node<T> * nodeBeforeptr = start;
			for (int i = 0; i < j - 1 && nodeBeforeptr->next->next; i++) nodeBeforeptr = nodeBeforeptr->next;

			Node<T> * removeNodeptr = nodeBeforeptr->next;
			nodeBeforeptr->next = removeNodeptr->next;
			delete removeNodeptr;
		}

		mySize--;
	}
}

//Return the value of the first node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getFirst(){
	if (start) {
		return start->value;
	} else {
		return T();
	}
}

//Return the value of the last node in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getLast(){
	if (start) {
		Node<T> * lastNodeptr = start;
		while (lastNodeptr->next) lastNodeptr = lastNodeptr->next;
		return lastNodeptr->value;
	} else {
		return T();
	}
}

//Return the value of the node at position j in the Linked List,
//If no first node, return the default constructed value: T()
template <class T>
T List<T>::getAt(int j){
	if (start) {
		Node<T> * iterator = start;
		for (int i = 0; i < j && iterator->next; i++) iterator = iterator->next;

		return iterator->value;
	} else {
		return T();
	}
}

//Return the position of the (first) node whose value is equal to the key
//Otherwise, return -1
template <class T>
int List<T>::find(T key){
	Node<T> * iterator = start;

	int index = 0;
	do {
		if (iterator->value == key) return index;
		index++;
	} while (iterator = iterator->next);

	return -1;
}
