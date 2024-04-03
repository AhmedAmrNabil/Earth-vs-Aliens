#ifndef LINKED_QUEUE_H_
#define LINKED_QUEUE_H_
#include "QueueADT.h" 
#include "DNode.h" 
#include <iostream>
using std::cout;


template<typename T>
class LinkedDeque : public QueueADT<T> {
private:
	DNode<T>* tail;

public:
	LinkedDeque() {
		tail = nullptr;
	}

	bool isEmpty() const override {
		return tail == nullptr;
	}


	bool enqueue(const T& newEntry) override {
		DNode<T>* newItem = new DNode<T>(newEntry);
		if (newItem == nullptr)return false;
		if (tail == nullptr)
			tail = newItem;
		else
			newItem->setNext(tail->getNext());

		tail->setNext(newItem);
		tail = newItem;
		return true;
	}

	bool dequeue(T& newEntry) override {
		if (isEmpty())return false;
		DNode<T>* item = tail->getNext();
		newEntry = item->getItem();

		if (item == tail)
			tail = nullptr;
		else
			tail->setNext(item->getNext());

		delete item;
		return true;
	}

	bool dequeueRear(T& newEntry) {
		if (isEmpty())return false;
		newEntry = tail->getItem();
		if (tail == tail->getNext()) {
			delete tail;
			tail = nullptr;
			return true;
		}

		DNode<T>* newTail = tail->getPrev();
		newTail->setNext(tail->getNext());
		delete tail;
		tail = newTail;
		return true;
	}

	bool peek(T& FrontEntry) const override {
		if (isEmpty())return false;
		FrontEntry = tail->getNext()->getItem();
		return true;
	}

	void print()
	{
		if (isEmpty())return;
		DNode<T>* ptr = tail->getNext();
		cout << "[" << ptr->getItem();
		if (ptr != tail) {

			int c = 1;
			while (ptr->getNext() != tail && c < 9) {
				ptr = ptr->getNext();
				cout << ", " << ptr->getItem();
				c++;
			}
			cout << ", " << tail->getItem();
		}
		cout << "]";
	}

	~LinkedDeque() {
		T tmp;
		while (dequeue(tmp));
	}

};






#endif
