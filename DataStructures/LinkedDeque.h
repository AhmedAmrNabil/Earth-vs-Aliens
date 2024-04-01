#ifndef LINKED_QUEUE_H_
#define LINKED_QUEUE_H_
#include "QueueADT.h" 
#include "Node.h" 


template<typename T>
class LinkedDeque : public QueueADT<T> {
private:
	Node<T>* tail;

public:
	LinkedDeque() {
		tail = nullptr;
	}

	bool isEmpty() const override {
		return tail == nullptr;
	}


	bool enqueue(const T& newEntry) override {
		Node<T>* newItem = new Node<T>(newEntry);
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
		Node<T>* item = tail->getNext();
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

		Node<T>* newTail = tail->getNext();

		while (newTail->getNext() != tail)
			newTail = newTail->getNext();

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

	void print() {
		Node<T>* ptr = tail->getNext();
		cout << "[" << ptr->getItem();
		do {
			ptr = ptr->getNext();
			cout << ", ";
			cout << ptr->getItem();
		} while (ptr != tail);
		cout << "]";
	}

	~LinkedDeque() {
		T tmp;
		while (dequeue(tmp));
	}

};






#endif
