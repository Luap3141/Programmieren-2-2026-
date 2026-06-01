#include "RecPoly.h"
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;

Integer* Integer::operator+(Ring *c) {
   Integer *other = dynamic_cast<Integer*>(c);
   if (other != nullptr) {
      return new Integer(value + other->value);
   }
   throw invalid_argument("Cannot add non-integer to integer");
}

Integer* Integer::operator*(Ring *c) {
   Integer *other = dynamic_cast<Integer*>(c);
   if (other != nullptr) {
      return new Integer(value * other->value);
   }
   throw invalid_argument("Cannot multiply non-integer to integer");
}

string Integer::str() {
      return to_string(value);
   }

bool Integer::operator==(Ring *c) {
   Integer *other = dynamic_cast<Integer*>(c);
   if (other != nullptr) {
      return value == other->value;
   }
   //here no error, if we compare two objects of different kinds, the result is just false.
   return false;
}

RecPoly::RecPoly(string var, int n, Ring **coeffs) {
   variable = var;
   if (n < 0) {
      throw invalid_argument("Size of Polynomial cannot be less than 0");
   }
   size = n;
   capacity = n + 1;
   coefficients = new Ring*[capacity];
   for (int i = 0; i < n; i++) {
      coefficients[i] = coeffs[i];
   }
}

RecPoly::RecPoly(RecPoly &p) {
   variable = p.variable;
   capacity = p.capacity;
   size = p.size;
   coefficients = new Ring*[p.capacity];
   for (unsigned i = 0; i < size; i++) {
      coefficients[i] = p.coefficients[i];
   }
}
RecPoly& RecPoly::operator=(RecPoly &p) {
   if (this == &p) {
      return *this;
   }
   variable = p.variable;
   capacity = p.capacity;
   size = p.size;
   coefficients = new Ring*[p.capacity];
   for (unsigned i = 0; i < size; i++) {
      coefficients[i] = p.coefficients[i];
   }
   return *this;
}

RecPoly::~RecPoly() {
   for (unsigned i = 0; i < capacity; i++) {
      delete coefficients[i];
   }
}

string RecPoly::str() {
   string out = "(";
   /*for (unsigned i = size; i >= 0; i--) {
      if (true) {
        //out = out + coefficients[i]->str() + variable + "^" + to_string(i + 1);
      }
   }*/
   out = out + ")";
   return out;
}

RecPoly* RecPoly::operator-() {
   RecPoly *output = new RecPoly(*this);
   for (unsigned i = 0; i < size; i++) {
      //I had coefficients[i] = -coefficients[i] and it didn't work, but this does. I don't know why.
      coefficients[i] = coefficients[i]->operator-();
   }
   return output;
}

RecPoly* RecPoly::operator+(Ring *c) {
   RecPoly *other = dynamic_cast<RecPoly*>(c);
   if (other == nullptr && this->variable != other->variable) {
      //I don't throw an exception, something else can be added to a polynomial by adding it to the 0th coefficient
      RecPoly *output = this->clone();
      output->coefficients[0] = coefficients[0]->operator+(other);
      return output;
   }
   RecPoly* output;
   unsigned newSize;
   if (this->size >= other->size) {
      newSize = size;
      output = this->clone();
   } else {
      newSize = other->size;
      output = other->clone();
   }
   for (unsigned i = 0; i < newSize; i++) {
      output->coefficients[i] = this->coefficients[i]->operator+(other->coefficients[i]);
   }
   return output;
}

RecPoly* RecPoly::operator*(Ring *c) {
   RecPoly *other = dynamic_cast<RecPoly*>(c);
   if (other == nullptr && this->variable != other->variable) {
      //I don't throw an exception, something else can be multiplied to a polynomial.
      RecPoly *output = this->clone();
      for (unsigned i = 0; i < size; i++) {
         output->coefficients[0] = coefficients[0]->operator*(other);
      }
      return output;
   }
   Ring** newCoeffs = new Ring*[this->size + other->size];
   RecPoly* output = new RecPoly(variable,this->size + other->size,newCoeffs);
   return output;
}

bool RecPoly::operator==(Ring* c) {
   RecPoly *other = dynamic_cast<RecPoly*>(c);
   if (other == nullptr) {
      return false;
   }
   if (this->variable != other->variable) {
      return false;
   }
   if (this->size != other->size) {
      return false;
   }
   for (unsigned i = 0; i < size; i++) {
      if (this->coefficients[i] != other->coefficients[i]) {
         return false;
      }
   }
   return true;
}
