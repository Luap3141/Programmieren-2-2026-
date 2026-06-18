/*
 * TemplateRecursiveMain.cpp
 *
 *  Created on: May 29, 2026
 *      Author: luap314
 */

#include "TemplateRecursive.h"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main() {

   //More testing
   random_device dev;
   mt19937 rng(dev());
   uniform_int_distribution<std::mt19937::result_type> dist(1, 10);

   vector<Integer*> a = { new Integer(dist(rng)), new Integer(dist(rng)),
         new Integer(dist(rng)), new Integer(dist(rng)) };
   vector<Integer*> b = { new Integer(dist(rng)), new Integer(dist(rng)),
         new Integer(dist(rng)) };
   vector<Integer*> c = { new Integer(dist(rng)), new Integer(dist(rng)) };
   UnivariatePoly *a1 = new UnivariatePoly(a, "x");
   UnivariatePoly *b1 = new UnivariatePoly(b, "x");
   UnivariatePoly *c1 = new UnivariatePoly(c, "x");
   cout << a1->str() << " | " << b1->str() << " | " << c1->str() << endl;
   //Because everything is a pointer, syntax like a1 + b1 doesn*t work
   //commutativity
   cout << "Testing Commutativity of + and *" << endl;
   cout << a1->operator+(b1)->str() << " =?= " << b1->operator+(a1)->str()
         << endl;
   cout << a1->operator*(b1)->str() << " =?= " << b1->operator*(a1)->str()
         << endl;
   //associativity
   cout << "Testing Associativity of + and *" << endl;
   cout << a1->operator+(b1->operator+(c1))->str() << " =?= "
         << a1->operator+(b1)->operator+(c1)->str() << endl;
   cout << a1->operator*(b1->operator*(c1))->str() << " =?= "
         << a1->operator*(b1)->operator*(c1)->str() << endl;
   //testing distributivity
   cout << "Testing Distributivity of + and *" << endl;
   cout << a1->operator*(b1)->operator+(a1->operator*(c1))->str() << " =?= "
         << a1->operator*(b1->operator+(c1))->str() << endl;
   //Success!

   cout << "This should be 0: " << a1->operator+(a1->operator-())->str()
         << endl;

   vector<UnivariatePoly*> a2 = { a1, b1, c1, a1 };
   vector<UnivariatePoly*> b2 = { a1, b1, a1 };
   vector<UnivariatePoly*> c2 = { b1, c1 };
   BivariatePoly *a3 = new BivariatePoly(a2, "y");
   BivariatePoly *b3 = new BivariatePoly(b2, "y");
   BivariatePoly *c3 = new BivariatePoly(c2, "y");

   //commutativity
   cout << "Testing Commutativity of + and *" << endl;
   cout << a3->operator+(b3)->str() << " =?= " << "\n"
         << b3->operator+(a3)->str() << endl;
   cout << a3->operator*(b3)->str() << " =?= " << "\n"
         << b3->operator*(a3)->str() << endl;
   //associativity
   cout << "Testing Associativity of + and *" << endl;
   cout << a3->operator+(b3->operator+(c3))->str() << " =?= " << "\n"
         << a3->operator+(b3)->operator+(c3)->str() << endl;
   cout << a3->operator*(b3->operator*(c3))->str() << " =?= " << "\n"
         << a3->operator*(b3)->operator*(c3)->str() << endl;
   //testing distributivity
   cout << "Testing Distributivity of + and *" << endl;
   cout << a3->operator*(b3)->operator+(a3->operator*(c3))->str() << " =?= "
         << "\n" << a3->operator*(b3->operator+(c3))->str() << endl;
   //Success!

   cout << "This should be 0: " << ((*a3)+(-*a3))->str()
         << endl;

   //Special Edge Case::
   unsigned test = 0;
   test = test - 2;
   test = test / 2;
   test = test + 1;

   vector<Integer*> test1 =
         { new Integer(0), new Integer(0), new Integer(test) };
   vector<Integer*> test2 = { new Integer(0), new Integer(2) };
   UnivariatePoly *testpoly1 = new UnivariatePoly(test1, "x");
   UnivariatePoly *testpoly2 = new UnivariatePoly(test2, "x");

   cout << "Is this 0, even though it should be of degree 3?: "
         << testpoly1->operator*(testpoly2)->str();

   for (auto i : a) {
      delete i;
   }
   for (auto i : b) {
      delete i;
   }
   for (auto i : c) {
      delete i;
   }
   for (auto i : test1) {
      delete i;
   }
   for (auto i : test2) {
      delete i;
   }
   delete a1, delete b1, delete c1;
   delete a3, delete b3, delete c3;
   delete testpoly1, delete testpoly2;
   return 0;
}
