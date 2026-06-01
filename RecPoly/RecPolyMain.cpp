#include "RecPoly.h"
#include <iostream>

using namespace std;

int main() {
   Ring* c[] = { new Integer(-5), new Integer(2),
   new Integer(0), new Integer(-3) };
   RecPoly* p = new RecPoly("x", 4, c); // p = -3x^3 + 2x - 5
   cout << p->str();
   RecPoly* q = // q = p+p
   dynamic_cast<RecPoly*>(p->operator+(p));
   cout << q->str();
   RecPoly* r = // r = p*q
   dynamic_cast<RecPoly*>(p->operator*(q));
   cout << r->str();

   delete c[0]; delete c[1]; delete c[2]; delete c[3];
   delete p; delete q; delete r;

	return 0;
}
