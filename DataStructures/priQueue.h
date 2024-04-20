#pragma once
#include "priNode.h"
#include <iostream>
using std::cout;

// This class impelements the priority queue as a sorted list (Linked List)
// The item with highest priority is at the front of the queue
template <typename T>
class priQueue {
    priNode<T>* head;
    int count;

   public:
    priQueue() : head(nullptr) {
        count = 0;
    }

    ~priQueue() {
        T tmp;
        int p;
        while (dequeue(tmp, p))
            ;
    }

    // insert the new node in its correct position according to its priority
    bool enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);
        if (newNode == nullptr)return false;
        if (head == nullptr || priority > head->getPri()) {
            newNode->setNext(head);
            head = newNode;
            ++count;
            return true;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
        ++count;
        return true;
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        --count;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
    
    void print()
    {
        int tmp;
        if (isEmpty())return;
        priNode<T>* ptr = head;
        cout << "[" << head->getItem(tmp);
        int c = 1;
        while (ptr->getNext() && c < 10) {
            ptr = ptr->getNext();
            cout << ", " << ptr->getItem(tmp);
            c++;
        }
        cout << "]";
    }
    int getCount() { return count; }
};
