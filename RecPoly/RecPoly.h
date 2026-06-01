#include <string>

using namespace std;

class Ring {
public:
// destructor
   virtual ~Ring() {
   }
// a heap-allocated duplicate of this element
   virtual Ring* clone() = 0;
// the string representation of this element
   virtual string str() = 0;
// the constant of the type of this element and the inverse of this element
   virtual Ring* zero() = 0;
   virtual Ring* operator-() = 0;
// sum and product of this element and c
   virtual Ring* operator+(Ring *c) = 0;
   virtual Ring* operator*(Ring *c) = 0;
// comparison function
   virtual bool operator==(Ring *c) = 0;
};

class Integer: public Ring {
   int value;
public:
// integer with value n (default 0)
   virtual ~Integer() {
   }
   ;
   Integer(int n = 0) {
      value = n;
   }
   virtual Integer* clone() {
      return new Integer(value);
   }
   virtual string str();
   virtual Integer* zero() {
      return new Integer(0);
   }
   virtual Integer* operator-() {
      return new Integer(-value);
   }
   virtual Integer* operator+(Ring *c);
   virtual Integer* operator*(Ring *c);
   virtual bool operator==(Ring *c);

};

class RecPoly: public Ring {
   unsigned capacity;
   unsigned size;
   Ring **coefficients;
   string variable;
public:
// polynomial with n>=0 coefficients and given variable name
   RecPoly(string var, int n, Ring **coeffs);
// copy constructor, copy assignment operator, destructor
   RecPoly(RecPoly &p);
   RecPoly& operator=(RecPoly &p);
   virtual ~RecPoly();

   virtual RecPoly* clone() {return new RecPoly(*this);}
   virtual string str();
   virtual RecPoly* zero() {return new RecPoly("",0,nullptr);}
   virtual RecPoly* operator-();
   virtual RecPoly* operator+(Ring* c);
   virtual RecPoly* operator*(Ring* c);
   virtual bool operator==(Ring *c);

   //Technical things:
   void sanitize();
};
