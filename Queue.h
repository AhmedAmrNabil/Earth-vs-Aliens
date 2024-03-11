#pragma once
#include "Node.h"
#include "LinkedList.h"
template <class T>
class Queue
{
private:
	LinkedList<T> L;
	Node<T>* Front;
	Node<T>* Rear;
public:
	Queue() {
		Front = nullptr;
		Rear = nullptr;
	}
	void enqueue(T value) {
		L.InsertEnd(value);
		Front = L.getHead();
		Rear = L.getTail();
	}
	void dequeue() {
		if(Front){
			L.DeleteBeg();
			Front = L.getHead();
			Rear = L.getTail();
		}
	}
	T front() {
		return Front->getItem();
	}
	void print() {
		L.PrintList();
	}
};

