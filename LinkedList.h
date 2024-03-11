#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T>* Head;  //Pointer to the head of the list
	Node<T>* Tail;
	int Count;
	bool merged;
	//You can add tail pointer too (depending on your problem)
public:

	LinkedList()
	{
		Head = nullptr;
		Tail = nullptr;
		Count = 0;
		merged = false;
	}
	Node<T>* getHead() {
		return Head;
	}
	Node<T>* getTail() {
		Node<T>* p = Head;
		if (!Head) return nullptr;
		while (p->getNext())
		{
			p = p->getNext();
		}
		return p;
	}
	//List is being destructed ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll(); 
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	void PrintList()	const
	{		
		cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "NULL\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		Count++;
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		if (!merged)
		{
				Node<T>* P = Head;
			while (Head)
			{
				P = Head->getNext();
				delete Head;
				Head = P;
			}
		}
	}
	T DeleteBeg() {
		Node<T>* P=Head->getNext();
		T value = Head->getItem();
		delete Head;
		Head = P;
		return value;
	}

	//[1]InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T& data) {
		Node<T>* N = new Node<T>(data);
		Node<T>* Temp = Head;
		if (Head != nullptr) {
			while (Temp->getNext()) {
				Temp = Temp->getNext();
			}
			Temp->setNext(N);
		}
		else {
			Head = N;
		}
		Count++;
	}

	////[2]Find 
	////searches for a given value in the list, returns true if found; false otherwise.
	//bool Find(T Key) {
	//	Node<T>* Temp = Head;
	//	while (Temp) {
	//		if (Temp->getItem()==Key) {
	//			return true;
	//		}
	//		Temp = Temp->getNext();
	//	}
	//	return false;
	//}

	////[3]CountOccurrence
	////returns how many times a certain value appeared in the list
	//int CountOccurrence(const T& value) {
	//	Node<T>* Temp = Head;
	//	int count = 0;
	//	while (Temp) {
	//		if (Temp->getItem() == value) {
	//			count++;
	//		}
	//		Temp = Temp->getNext();
	//	}
	//	return count;
	//}

	////[4] DeleteFirst
	////Deletes the first node in the list
	//void DeleteFirst() {
	//		Node<T>* Temp = Head->getNext();
	//		delete Head;
	//		Head = Temp;
	//		Count--;
	//}


	////[5] DeleteLast
	////Deletes the last node in the list
	//void DeleteLast() {
	//	if (!Head->getNext()) delete Head;
	//	else
	//	{
	//		Node<T>* Temp = Head;
	//		while ((Temp->getNext())->getNext()) {
	//			Temp = Temp->getNext();
	//		}
	//		delete Temp->getNext();
	//		Temp->setNext(nullptr);
	//	}
	//	Count--;
	//}

	////[6] DeleteNode
	////deletes the first node with the given value (if found) and returns true
	////if not found, returns false
	////Note: List is not sorted
	//bool DeleteNode(const T& value) {
	//	if (Head->getItem() == value) {
	//		DeleteFirst();
	//	}
	//	else
	//	{
	//		Node<T>* Temp1 = Head;
	//		Node<T>* Temp2 = new Node<T>();
	//		while (Temp1) {
	//			if ((Temp1->getNext())->getItem() == value) {
	//				Temp2 = Temp1->getNext()->getNext();
	//				delete Temp1->getNext();
	//				Temp1->setNext(Temp2);
	//				return true;
	//			}
	//			Temp1 = Temp1->getNext();
	//		}
	//		return false;
	//	}
	//	Count--;
	//}

	////[7] DeleteNodes
	////deletes ALL node with the given value (if found) and returns true
	////if not found, returns false
	////Note: List is not sorted
	//bool DeleteNodes(const T& value)
	//{
	//	int c = CountOccurrence(value);
	//	for (int i = 1; i <= c; i++) {
	//		DeleteNode(value);
	//	}
	//	return c;
	//}

	////[8]Merge
	////Merges the current list to another list L by making the last Node in the current list 
	////point to the first Node in list L
	//void Merge(LinkedList& L)
	//{
	//	Node<T>* Temp = Head;
	//	while (Temp->getNext()) {
	//		Temp = Temp->getNext();
	//	}
	//	Temp->setNext(L.Head);
	//	L.merged=true;
	//}

	////[9] Reverse
	////Reverses the linked list (without allocating any new Nodes)
	//void Reverse()
	//{
	//	if (!Head || !Head->getNext()) return; 
	//	Node<T>* N = Head->getNext();	
	//	Node<T>* P = nullptr;			   
	//	Node<T>* C = Head;	
	//	while (C)				
	//	{
	//		N = C->getNext();
	//		C->setNext(P);
	//		P = C;
	//		C = N;	
	//	}
	//	Head = P;
	//}

};
#endif	