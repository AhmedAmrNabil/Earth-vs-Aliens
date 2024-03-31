#pragma once

#include "StackADT.h"
#include "Node.h"

#include <iostream>
using namespace std;

template<typename T>
class LinkedListStack : public StackADT<T>
{
private:
	Node<T>* top;
public:
	bool isEmpty() const
	{
		return (top == nullptr);
	}
	bool push(const T& newEntry)
	{
		Node<T>* newNode = new Node <T> (newEntry);
		if (!newNode)return false;
		if (!top) 
		{
			top = newNode;
			return true;
		}
		else 
		{
			newNode->setNext(top);
			top = newNode;
			return true;
		}
	}
	bool pop(T& TopEntry) 
	{
		if (!top)return false;
		TopEntry = top->getItem();
		Node<T>* temp = top;
		top = top->getNext();
		delete temp;
		return true;
	}
	bool peek(T& TopEntry) const
	{
		if (!top)return false;
		TopEntry = top->getItem();
		return true;
	}
	~LinkedListStack()
	{
		Node<T>* temp = top;
		while (top) 
		{
			top = top->getNext();
			delete temp;
			temp = top;
		}
	}
};

