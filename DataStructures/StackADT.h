//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** @file StackADT.h */

#ifndef STACK_ADT_
#define STACK_ADT_

template<typename T>
class StackADT
{
public:
   /** checks whether this stack is empty.
    @return  True if the stack is empty, or false if not. */
   virtual bool isEmpty() const = 0;
   
   /** Adds a new entry to the top of this stack.
    @post  If the operation was successful, newEntry is at the top of the stack.
    @param newEntry  The object to be added as a new entry.
    @return  True if the addition is successful or false if not. */
   virtual bool push(const T& newEntry) = 0;
   
   /** Copies the top item of the stack to the passed parameter and removes it from stack
    @post  If the operation was successful, the top item of the stack
       has been copied to TopEntry parameter.
    @return  True if the removal is successful or false if not. */
   virtual bool pop(T& TopEntry) = 0;
   
   /** Copies the top item of the stack to the passed parameter without removing it from stack
    @pre  The stack is not empty.
    @post  If the operation was successful, the top item of the stack
       has been copied to TopEntry parameter.
    @return  True if stack is not empty or false if not. */
   virtual bool peek(T& TopEntry) const = 0 ;
   
   /** Destroys this stack and frees its assigned memory. */
   virtual ~StackADT() { }
}; // end StackADT
#endif