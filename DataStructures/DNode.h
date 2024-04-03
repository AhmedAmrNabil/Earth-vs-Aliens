#pragma once

template <typename T>
class DNode {
private:
	T item;         // A data item
	DNode<T>* next;  // Pointer to next node
	DNode<T>* prev;  // Pointer to previous node
public:
	DNode(const T& r_Item, DNode<T>* nextNodePtr = nullptr, DNode<T>* prevNodePtr = nullptr) {
		item = r_Item;
		next = nextNodePtr;
		prev = prevNodePtr;
	}
	DNode() {
		next = nullptr;
		prev = nullptr;
	}
	void setNext(DNode<T>* nextNodePtr) {
		this->next = nextNodePtr;
		if (nextNodePtr != nullptr)
			nextNodePtr->prev = this;
	}
	void setPrev(DNode<T>* prevNodePtr) {
		this->prev = prevNodePtr;
		if (prevNodePtr != nullptr)
			prevNodePtr->next = this;
	}
	DNode<T>* getNext() const { return next; }
	DNode<T>* getPrev() const { return prev; }
	void setItem(const T& r_Item) { item = r_Item; }
	T getItem() const { return item; }
};