#ifndef STACK_H
#define STACK_H
/* Stack.h
 *
 * a templated stack based on a linked list
 * EECS 280 Project 5
 */

#include "List.h"
#include <cstddef>
#include <cassert>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// DO NOT MODIFY THE CLASS'S PUBLIC INTERFACE OR PRIVATE VARIABLES.
template <typename T>
class Stack {
  //OVERVIEW: a templated, linked-list-based stack
  // The T is type of value stored, and it must implement operator<<

 public:
  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy stacks.

  //EFFECTS:  returns true if the stack is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this Stack
  int size() const;

  //REQUIRES: stack is non-empty. Assert false if it is empty.
  //MODIFIES: this
  //EFFECTS:  removes the item at the top and returns it.
  // E.g., pop(S.push(item)) results in the stack being equivalent to S
  // and returns the item.
  T pop();

  //REQUIRES: stack be non-empty. Assert false if it is empty.
  //EFFECTS:  returns a reference the top element from the stack without
  // popping it. Note: Since a reference is returned, potentially, the caller
  // can use the call to change the top without doing a pop/push. You should
  // test for that in your tests.
  // E.g., top(S.push(item)) results in a reference to item.
  T & top() const;

  //MODIFIES: this
  //EFFECTS: pushes an item onto the top of the stack
  void push(const T &item);

  //EFFECTS: returns the number of elements in the stack for which
  //  f(datum) is true, where datum is the value stored in the stack's
  //  elements.  We use a template for Comparer type so that f can
  //  either be a functor or a function pointer.
  // E.g., count_if(pred) is 0 for an empty stack. For a non-empty stack,
  // say S.push(item), where item is pushed on a stack S, count_if(pred) will be
  // the sum of S.count_if(pred) and either 1 or 0 depending on
  // whether item satisfies pred, respectively.
  template <typename Predicate>
  int count_if(Predicate pred) const;

  template <typename U>
  friend std::ostream &operator<<(std::ostream &os, const Stack<U> &obj);

private:
  /* You must make use of List's interface to implement the stack.
   * You must not make changes to the private section.
   */
  List<T> list;
};


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface, although you
// may add the Big Three if needed

//EFFECTS: print all the elements of the stack, starting from the
// top element. Each element printed is followed by a space,
// including the last element. Do not print a newline.
// If the stack is empty, print nothing. You can modify Stack class
// if necessary to make this function a friend so that this function can
// access internal data within Stack.
//
// Hint: for this function to access the private "list" variable, you will
// need to declare it as a "friend" function in the class declaration above.
template <typename U>
std::ostream &operator<<(std::ostream &os, const Stack<U> &obj) {
  for(typename List<U>::Iterator i = obj.list.begin(); i != obj.list.end(); ++i) {
    os << *i << " ";
	}
  return os;
}

  //EFFECTS:  returns true if the stack is empty
template <typename T>
bool Stack<T>::empty() const {
  return list.empty();
}
  //EFFECTS: returns the number of elements in this Stack
template <typename T>
int Stack<T>::size() const {
  return list.size();
}

  //REQUIRES: stack is non-empty. Assert false if it is empty.
  //MODIFIES: this
  //EFFECTS:  removes the item at the top and returns it.
  // E.g., pop(S.push(item)) results in the stack being equivalent to S
  // and returns the item.
template <typename T>
T Stack<T>::pop(){
  assert(!empty());
  T temp = list.front();
  list.pop_front();
  return temp;
}

  //REQUIRES: stack be non-empty. Assert false if it is empty.
  //EFFECTS:  returns a reference the top element from the stack without
  // popping it. Note: Since a reference is returned, potentially, the caller
  // can use the call to change the top without doing a pop/push. You should
  // test for that in your tests.
  // E.g., top(S.push(item)) results in a reference to item.
template <typename T>
T & Stack<T>::top() const {
  assert(!empty());
  return list.front();
}


  //MODIFIES: this
  //EFFECTS: pushes an item onto the top of the stack
template <typename T>
void Stack<T>::push(const T &item){
  list.push_front(item);
}

  //EFFECTS: returns the number of elements in the stack for which
  //  f(datum) is true, where datum is the value stored in the stack's
  //  elements.  We use a template for Comparer type so that f can
  //  either be a functor or a function pointer.
  // E.g., count_if(pred) is 0 for an empty stack. For a non-empty stack,
  // say S.push(item), where item is pushed on a stack S, count_if(pred) will be
  // the sum of S.count_if(pred) and either 1 or 0 depending on
  // whether item satisfies pred, respectively.
template <typename T>
template <typename Predicate>
int Stack<T>::count_if(Predicate pred) const {
  int count = 0;
  for(typename List<T>::Iterator i = list.begin(); i != list.end(); ++i) {
		if (pred(*i)) ++count;
	}
  return count;
} 
#endif /* STACK_H */
