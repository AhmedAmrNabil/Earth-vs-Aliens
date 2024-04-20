#ifndef LINKED_DEQUEUE_H
#define LINKED_DEQUEUE_H
#include <iostream>

#include "DNode.h"
#include "QueueADT.h"
using std::cout;

template <typename T>
class LinkedDeque : public QueueADT<T> {
   private:
    DNode<T>* tail;
    int count;

   public:
    LinkedDeque() {
        tail = nullptr;
        count = 0;
    }

    bool isEmpty() const override {
        return tail == nullptr;
    }

    bool enqueue(const T& newEntry) override {
        DNode<T>* newItem = new DNode<T>(newEntry);
        if (newItem == nullptr) return false;
        if (tail == nullptr)
            tail = newItem;
        else
            newItem->setNext(tail->getNext());
        tail->setNext(newItem);
        tail = newItem;
        ++count;
        return true;
    }

    bool enqeueFront(const T& newEntry) {
        DNode<T>* newItem = new DNode<T>(newEntry);
        if (newItem == nullptr) return false;
        if (tail == nullptr)
            tail = newItem;
        else
            newItem->setNext(tail->getNext());
        tail->setNext(newItem);
        ++count;
        return true;
    }

    bool peekRear(T& backEntry) {
        if (isEmpty())return false;
        backEntry = tail->getItem();
        return true;
    }

    bool dequeue(T& backEntry) override {
        if (isEmpty()) return false;
        DNode<T>* item = tail->getNext();
        backEntry = item->getItem();

        if (item == tail)
            tail = nullptr;
        else
            tail->setNext(item->getNext());

        delete item;
        --count;
        return true;
    }

    bool dequeueRear(T& newEntry) {
        if (isEmpty()) return false;
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
        --count;
        return true;
    }

    bool peek(T& FrontEntry) const override {
        if (isEmpty()) return false;
        FrontEntry = tail->getNext()->getItem();
        return true;
    }

    void print() {
        if (isEmpty()) return;
        DNode<T>* ptr = tail->getNext();
        cout << "[" << ptr->getItem();
        if (ptr != tail) {
            while (ptr->getNext() != tail) {
                ptr = ptr->getNext();
                cout << ", " << ptr->getItem();
            }
            cout << ", " << tail->getItem();
        }
        cout << "]";
    }

    ~LinkedDeque() {
        T tmp;
        while (dequeue(tmp));
    }
    int getCount() { return count; }
};

#endif
