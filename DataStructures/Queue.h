#pragma once
#include "LinkedList.h"
#include "Node.h"
template <class T>
class Queue {
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
    T dequeue() {
        if (Front) {
            T value = L.DeleteBeg();
            Front = L.getHead();
            Rear = L.getTail();
            return value;
        }
    }
    T front() {
        return Front->getItem();
    }
    void print() {
        L.PrintList();
    }
};
