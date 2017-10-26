//============================================================================
// Name        : Units-Bjarne-Style.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

template<int M, int K, int S> struct Unit {  // a unit in the MKS system
  enum { m=M, kg=K, s=S };
};
template<typename Unit>  // a magnitude with a unit
struct Value {
  double val;     // the magnitude
  explicit Value(double d) : val(d) {}  // construct a Value from a double
};


int main() {

	using Speed = Value<Unit<1,0,-1>>;    // meters/second type
	using Acceleration = Value<Unit<1,0,-2>>;   // meters/second/second type



	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
