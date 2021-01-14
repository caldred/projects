#include "List.h"

#include <iostream>

using namespace std;

int main() {
  List<int> my_list;
  my_list.push_front(1);
  my_list.push_back(2);
  my_list.push_back(3);

  assert(my_list.front() == 1);
  cout << my_list.front()<< endl;
  my_list.pop_front();
  assert(my_list.back() == 3);
  my_list.pop_back();
  
  cout << "PASS" << endl;
}
