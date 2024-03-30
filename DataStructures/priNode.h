#pragma once
template <typename T>
class priNode {
   private:
    T item;            // A data item
    int pri;           // priority of the item
    priNode<T>* next;  // Pointer to next node
   public:
    priNode(const T& r_Item, int PRI, priNode<T>* nextNodePtr= nullptr) {
        setItem(r_Item, PRI);
        next = nextNodePtr;
    }
    void setItem(const T& r_Item, int PRI) {
        item = r_Item;
        pri = PRI;
    }
    void setNext(priNode<T>* nextNodePtr) { next = nextNodePtr; }

    T getItem(int& PRI) const {
        PRI = pri;
        return item;
    }

    priNode<T>* getNext() const { return next; }

    int getPri() const { return pri; }
};  // end Node
