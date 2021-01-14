#ifndef LIST_H
#define LIST_H
/* List.h
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 5
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  //EFFECTS:  returns true if the list is empty
  bool empty() const;

  //EFFECTS: returns the number of elements in this List
  int size() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the first element in the list
  T & front() const;

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the last element in the list
  T & back() const;

  //MODIFIES: this
  //EFFECTS:  inserts i into the front of the list
  void push_front(const T &datum);

  //MODIFIES: this
  //EFFECTS:  inserts i into the back of the list
  void push_back(const T &datum);

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the front of the list
  void pop_front();

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the back of the list
  void pop_back();
  
  ~List();
  List();
  List(const List &other);
  List & operator= (const List &rhs);

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Li


private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
  };

  //MODIFIES: this
  //EFFECTS:  copies all nodes from l to this
  void copy_all(const List<T> &l);

  //MODIFIES: this
  //EFFECTS:  removes all nodes
  void pop_all();

  Node *first;   // points to first Node in list, or 0 if list is empty
  Node *last;    // points to last Node in list, or 0 if list is empty

public:
  ////////////////////////////////////////
	class Iterator {
    //OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator& operator--() {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }
    // create a default Iterator, which points "past the end", AKA NULL, AKA 0
    Iterator() : node_ptr(0) {}
				
    // get the T at the current Iterator position
    T& operator* () const {
      assert(node_ptr);
      return node_ptr->datum;
    }

    // move Iterator to next position (prefix)
    // REQUIRES: Iterator is not at default position
    Iterator& operator++ () { 
      assert(node_ptr);
      node_ptr = node_ptr->next;
      return *this;
    }

    // compare two Iterator objects by the their position
    bool operator!= (Iterator rhs) const { return
        node_ptr != rhs.node_ptr;
    }

    // compare two Iterator objects by the their position
    bool operator== (Iterator rhs) const {
      return node_ptr == rhs.node_ptr;
    }

  private:
    Node *node_ptr; //current Iterator position is a List node
      // move Iterator to next position (postfix)

    friend class List; //needed so that List::begin() can access private ctor

    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first node
  Iterator begin() const {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const{
    return Iterator();
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: this, may invalidate other list iterators
  //EFFECTS: Removes a single element from the list container
  void erase(Iterator i){
    Iterator j(i.node_ptr);
		Node* victim = i.node_ptr;
    if(i.node_ptr->next == 0) {
	 		victim = last;
			if (size() == 1) {
				first = last = 0;
			}
			else {
				last = last->prev;
				last->next = 0;
			}
    }
    else if(i.node_ptr->prev == 0) {
		  victim = first;
			if (size() == 1) {
				first = last = 0;
			}
			else {
				first = first->next;
				first->prev = 0;
			}
    }
    else{
      --i;
      ++j;
      i.node_ptr->next = j.node_ptr;
      j.node_ptr->prev = i.node_ptr;
    }
    delete victim;
    victim = 0;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum){
    Iterator j(i.node_ptr);
    Node *p = new Node;
    p->datum = datum;
		if(empty()){
			p->next = p->prev = 0;
			return;
		}
    --i;
    p->next = j.node_ptr;
    p->prev = i.node_ptr;
    if(j.node_ptr != 0){
      j.node_ptr->prev = p;
    }
    if(i.node_ptr != 0) {
      i.node_ptr->next = p;
    }
  }
};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.
//EFFECTS:  returns true if the list is empty
  template <typename T>
  bool List<T>::empty() const{
    return first == 0;
  }

  //EFFECTS: returns the number of elements in this List
  template <typename T>
  int List<T>::size() const{
		if(empty()) return 0;
		Iterator i = begin();
		int count = 0;
		while(i != end()) {
			++i;
			++count;
		}
		return count;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the first element in the list
  template <typename T>
  T & List<T>::front() const{
    assert(first);
    return (first->datum);
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns a reference to the last element in the list
  template <typename T>
  T & List<T>::back() const{
    assert(last);
    return (last->datum);
  }

  //MODIFIES: this
  //EFFECTS:  inserts i into the front of the list
  template <typename T>
  void List<T>::push_front(const T &datum){
    Node *p = new Node;
    p->datum =datum;
    p->prev = NULL;
    if (empty()) {
			first = last = p;
			p->next = NULL;
		}
    else {
      p->next = first;
      first->prev = p;
      first = p;
    }
  }

  //MODIFIES: this
  //EFFECTS:  inserts i into the back of the list
  template <typename T>
  void List<T>::push_back(const T &datum){
    Node *p = new Node;
    p->datum = datum;
    p->next = NULL;
    if (empty()) first = last = p;
    else {
      p->prev = last;
      last->next = p;
      last = p;
    }
  }

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the front of the list
  template <typename T>
  void List<T>::pop_front(){
    assert(!empty());
    Node *victim = first;
		if (size() == 1) {
			first = last = 0;
			delete victim;
			victim = 0;
		}
		else {
		  first = first->next;
		  first->prev = 0;
		  delete victim;
		  victim = 0;
		}
  }

  //REQUIRES: list is not empty
  //MODIFIES: this
  //EFFECTS:  removes the item at the back of the list
  template <typename T>
  void List<T>::pop_back(){
    assert(!empty());
    Node *victim = last;
		if (size() == 1) {
			first = last = 0;
			delete victim;
			victim = 0;
		}
		else {
		  last = last->prev;
		  last->next = 0;
		  delete victim;
		  victim = 0;
		}
  }
  
  template <typename T>
  List<T>::List() : first(0), last(0) {}

  template <typename T>
  List<T>::~List() {
    pop_all();
		std::cout << "Destructor's done!\n";
  }
  template <typename T>
  List<T>::List(const List &other) : first(0), last(0) {
    copy_all(other);
  }
  
  template <typename T>
  List<T> & List<T>::operator= (const List &rhs) {
    if (this == &rhs) return *this;
    pop_all();
    copy_all(rhs);
    return *this;
  }

    //MODIFIES: this
  //EFFECTS:  copies all nodes from l to this
  template <typename T>
  void List<T>::copy_all(const List<T> &l){
    for (Node *p = l.first; p!=0; p=p->next)
      push_back(p->datum);
  }

  //MODIFIES: this
  //EFFECTS:  removes all nodes
  template <typename T>
  void List<T>::pop_all(){
    while (!empty()){
      pop_front();
    }
  }


#endif
