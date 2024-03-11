#pragma once
#include "LinkedList.h"
#include "Node.h"
template <class T>
class Stack {
   private:
    LinkedList<T> L;
    Node<T>* Top;

   public:
    Stack() {
        Top = nullptr;
    }
    void push(T value) {
        L.InsertBeg(value);
        Top = L.getHead();
    }
    T pop() {
        if (Top) {
            T value = L.DeleteBeg();
            Top = L.getHead();
            return value;
        }
    }
    bool isEmpty() {
        return (!Top);
    }
    T peek() {
        return Top->getItem();
    }
    void Print() {
        L.PrintList();
    }
};
