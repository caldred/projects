#include <iostream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <cmath>
#include "Rational.h"
#include "Stack.h"

using namespace std;

class EqualsN {
 Rational n;
public:
  EqualsN(Rational n_in) : n(n_in) {}
  bool operator() (Rational input) { 
		return (input == n);
	}
};

int main() {
  Stack<Rational> s;
  while(!cin.eof()){
    string input;
    cin >> input;
		if(input == "0") s.push(0);
    else if(atoi(input.c_str())){
      s.push(atoi(input.c_str()));
    }
    else if(input == "+"){
      Rational rhs = s.pop();
      Rational lhs = s.pop();
      Rational result = lhs + rhs;
      s.push(result);
    }
    else if(input == "-"){
      Rational rhs = s.pop();
      Rational lhs = s.pop();
      Rational result = lhs - rhs;
      s.push(result);
    }
    else if(input == "*"){
      Rational rhs = s.pop();
      Rational lhs = s.pop();
      Rational result = lhs * rhs;
      s.push(result);
    }
    else if(input == "/"){
      Rational rhs = s.pop();
      Rational lhs = s.pop();
      Rational result = lhs / rhs;
      s.push(result);
    }
    else if(input == "d"){
      Rational top = s.pop();
      s.push(top);
      s.push(top);
    }
    else if(input == "p"){
      Rational top = s.top();
      cout << top  << endl;
    }
    else if(input == "r"){
      Rational first = s.pop();
      Rational second = s.pop();
      s.push(first);
      s.push(second);
    }
    else if(input == "c"){
      while(!s.empty()){
	s.pop();
      }
    }
    else if(input == "a"){
      cout << s << endl;
    }
    else if(input == "n"){
      s.top()=s.top()*-1;
    }
    else if(input == "m"){
      EqualsN eN(s.pop());
      int matches = s.count_if(eN);
      s.push(matches);
    }
    else if(input == "q"){
      return 0;
    }
  }
}
