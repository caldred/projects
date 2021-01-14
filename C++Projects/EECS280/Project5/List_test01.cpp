#include "List.h"

#include <iostream>

using namespace std;

void print_int_list(List<int> l) {
	for (List<int>::Iterator i = l.begin(); i != l.end(); ++i)
		cout << *i << endl;
}
	

int main() {
  List<int> my_list;
	
	assert(my_list.size() == 0);
  my_list.push_front(1);
  my_list.push_back(2);
  my_list.push_back(3);
	for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) cout << *i << endl;
	cout << "List size: " << my_list.size() << endl;
	assert(my_list.size() == 3);
	my_list.push_front(0);
	my_list.push_back(5);
	for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) cout << *i << endl;
	cout << "List size: " << my_list.size() << endl;
	assert(my_list.size() == 5);

  assert(my_list.front() == 0);
  my_list.pop_front();
	assert(my_list.size() == 4);
	List<int>::Iterator i = my_list.begin();
	while(*i != 5) ++i;
	my_list.insert(i, 4);
	for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) cout << *i << endl;
	assert(my_list.size() == 5);
  assert(my_list.back() == 5);
	List<int>::Iterator j = my_list.begin();
	my_list.erase(j);
	for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) cout << *i << endl;
	assert(my_list.front() = 2);
  my_list.pop_back();
	assert(my_list.back() == 4);
	assert(my_list.size() == 3);
	for (List<int>::Iterator i = my_list.begin(); i != my_list.end(); ++i) cout << *i << endl;
	List<int>::Iterator k = my_list.begin();
	++k;
	my_list.erase(k);
	assert(my_list.front() == 2);
	assert(my_list.back() == 4);
	assert(my_list.size() == 2);
  cout << "PASS" << endl;
}
