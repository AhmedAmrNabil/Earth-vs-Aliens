#pragma once
#include "priNode.h"

// This class impelements the priority queue as a sorted list (Linked List)
// The item with highest priority is at the front of the queue
template <typename T>
class priQueue {
    priNode<T>* head;

   public:
    priQueue() : head(nullptr) {}

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p))
            ;
    }

    // insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri()) {
            newNode->setNext(head);
            head = newNode;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem();
        pri = head->getPri();
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
    
    void print()
    {
        int pri;
        priNode<T>* ptr = head->getNext();
        cout << "[" << head->getItem(pri);
        int c = 1;
        do {
            cout << ", ";
            cout << ptr->getItem(pri);
            c++;
            ptr = ptr->getNext();
        } while (ptr && c!=10);
        cout << "]";
    }
};
