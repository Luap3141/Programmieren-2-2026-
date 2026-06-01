/*
 * DistPolyMain.cpp
 *
 *  Created on: Apr 23, 2026
 *      Author: luap314
 */

#include "DistPoly.h"
#include <string>
#include <iostream>
#include <random>

using namespace std;

int main() {

   // some exponent vectors ("power products")
   int e1[2] = { 1, 2 };
   int e2[2] = { 2, 1 };
   int e3[2] = { 1, 0 };
   int e4[2] = { 0, 1 };
   int e5[2] = { 0, 0 };
   int e6[2] = { 2, 2 };

   string vars2[2] = { "x", "y" };
   // construct zero polynomial in two variables, then add monomials

   DistPoly p(2, vars2);
   p.add(3, e1).add(5, e2).add(7, e3).add(11, e4).add(13, e5);
   // construct zero polynomial in two variables, then add monomials
   DistPoly q(2, vars2);
   q.add(11, e4).add(-3, e2).add(2, e6).add(-2, e2);
   // print p and q
   cout << p.str() << endl;
   cout << q.str() << endl;

   // set p to p+2*q and print it
   DistPoly r = p;
   r.add(q).add(q);
   p = r;
   cout << p.str() << endl;

   //My Own Tests

   //rng stuff
   default_random_engine rng;
   random_device rand_dev;
   rng.seed(rand_dev());
   uniform_int_distribution<int> next_r(0, 10);

   //Single Var

   string vars1[1] = { "x" };

   int a1[1] = { next_r(rng) };
   int a2[1] = { next_r(rng) };
   int a3[1] = { next_r(rng) };
   int a4[1] = { next_r(rng) };

   DistPoly Test(1, vars1);
   DistPoly Test1(1, vars1);

   Test.add(Test1);

   //0 Polynomial
   cout << Test.str() << endl;

   Test.add(next_r(rng), a1).add(next_r(rng), a2).add(next_r(rng), a3).add(
         next_r(rng), a4);

   cout << Test.str() << endl;

   //Will this output 0?

   Test1.add(5, a2).add(-5, a2);
   cout << Test1.str() << endl;

   string vars3[3] = { "x", "y", "z" };

   int b1[3] = { next_r(rng), next_r(rng), next_r(rng) };
   int b2[3] = { next_r(rng), next_r(rng), next_r(rng) };

   DistPoly Test3(3, vars3);

   //It adds from left to right

   Test3.add(1, b1).add(Test3).add(4, b2).add(Test3);

   //Therefore we should have one coefficient 4 and one 8;

   cout << Test3.str() << endl;

   try {
      DistPoly n(3, vars3);
      n.add(3, e1);
      n.add(Test1);
   } catch (const std::exception &e) {
      std::cout << "Error: " << e.what() << std::endl;
   }
   return 0;
}

