/*
 * TemplateRecursive.h
 *
 *  Created on: May 29, 2026
 *      Author: luap314
 */

#ifndef TEMPLATERECURSIVE_H_
#define TEMPLATERECURSIVE_H_

#include <vector>
#include <iostream>
#include <string>

using namespace std;

template<class Ring> class RecPoly {
   vector<Ring*> coeffs;
   string variable;
public:

   /*
    * RecPoly()
    * Constructor
    */
   RecPoly() :
         coeffs( { }), variable("x") {
   }
   /*
    * RecPoly(newCoffs, newVar)
    * Constructs a Polynomial with a given vector and variable name
    */
   RecPoly(vector<Ring*> newCoeffs, string newVar) {
      coeffs = newCoeffs;
      variable = newVar;
   }

   /*
    * clone()
    * Creates a deep copy on the heap
    */
   RecPoly* clone() {
      return new RecPoly(coeffs, variable);
   }

   /*
    * str()
    * returns string-representation of polynomial
    */
   string str() {
      if (coeffs.size() == 0) {
         return "0";
      }
      if (coeffs.size() == 1) {
         return coeffs[0]->str();
      }
      if (coeffs.size() == 2) {
         return "(" + coeffs[0]->str() + " + " + coeffs[1]->str() + variable
               + ")";
      }
      string out = "(" + coeffs[0]->str() + " + " + coeffs[1]->str() + variable
            + " + ";
      for (unsigned i = 2; i < coeffs.size() - 1; i++) {
         out += coeffs[i]->str() + variable + "^" + to_string(i) + " + ";
      }
      out += coeffs.back()->str() + variable + "^"
            + to_string(coeffs.size() - 1) + ")";
      return out;
   }

   /*
    * static zero()
    * returns the additive neutral element, which is a 0-polynomial
    */
   static RecPoly* zero() {
      //Probably not going to work as intended because how do you tell zero
      //what variable it has to have, but I don*t know how to fix it
      return new RecPoly( { }, "x");
   }

   /*
    * operator+(other)
    * returns this + other
    * school-algorithm
    */
   RecPoly* operator+(RecPoly *other) {
      if (this->variable != other->variable) {
         //Maybe more refined behaviour can be added later
         throw invalid_argument("Polynomials of different variable added");
      }
      vector<Ring*> output(max(this->coeffs.size(), other->coeffs.size()));
      if (this->coeffs.size() < other->coeffs.size()) {
         for (unsigned i = 0; i < this->coeffs.size(); i++) {
            output[i] = this->coeffs[i]->operator+(other->coeffs[i]);
         }
         for (unsigned i = this->coeffs.size(); i < other->coeffs.size(); i++) {
            output[i] = other->coeffs[i];
         }
      } else {
         for (unsigned i = 0; i < other->coeffs.size(); i++) {
            output[i] = this->coeffs[i]->operator+(other->coeffs[i]);
         }
         for (auto i = other->coeffs.size(); i < this->coeffs.size(); i++) {
            output[i] = this->coeffs[i];
         }
      }
      RecPoly *out = new RecPoly(output, this->variable);
      out->sanitize();
      return out;
   }

   /*
    * operator-()
    * returns additive inverse
    */
   RecPoly* operator-() {
      vector<Ring*> output(this->coeffs.size());
      for (unsigned i = 0; i < this->coeffs.size(); i++) {
         output[i] = coeffs[i]->operator-();
      }
      return new RecPoly(output, this->variable);
   }

   /*
    * operator*(other)
    * returns this*other
    * school algorithm
    */
   RecPoly* operator*(RecPoly *other) {
      if (this->variable != other->variable) {
         //Maybe more refined behaviour can be added later
         throw invalid_argument("Polynomials of different variable multiplied");
      }
      vector<Ring*> output(this->coeffs.size() + other->coeffs.size() - 1);
      for (unsigned i = 0; i < output.size(); i++) {
         output[i] = Ring::zero();
      }
      for (unsigned i = 0; i < this->coeffs.size(); i++) {
         for (unsigned j = 0; j < other->coeffs.size(); j++) {
            Ring *summand = this->coeffs[i]->operator*(other->coeffs[j]);
            output[j + i] = output[j + i]->operator+(summand);
         }
      }
      RecPoly *out = new RecPoly(output, this->variable);
      //For safety, we remove leading zeros. Algebra tells us that
      //there are none, other than in extreme edge cases.
      out->sanitize();
      return out;
   }

   /*
    * operator**(other)
    * compares equality of two polynomials
    */
   bool operator==(RecPoly &other) {
      if (this->variable != other.variable
            || this->coeffs.size() != other.coeffs.size()) {
         //more refined behaviour could be added later
         return false;
      }
      for (unsigned i = 0; i < this->coeffs.size(); i++) {
         if (!(this->coeffs[i] == other.coeffs[i])) {
            return false;
         }
      }
      return true;
   }

   /*
    * degree()
    * returns degree of the polynomial.
    * If the polynomial is 0, it should return negative infinity but can't, because
    * that would not be an integer. Therefore it returns 0 instead.
    */
   int degree() {
      return min(coeffs.size() - 1,0);
   }

   /*
    * sanitize()
    * brings polynomial into canonical form.
    * Here, this means that leading zeroes get deleted.
    */
   void sanitize() {
      //brings polynomial into canonical form (in this ase, just removes leading zeroes.
      for (int i = coeffs.size() - 1; i >= 0; i--) {
         if (!(*coeffs[i] == *Ring::zero())) {
            return;
         }
         coeffs.pop_back();
      }
   }
};

class Integer {
   int value = 0;
public:

   /*
    * Integer()
    * default constructor
    */
   Integer() {
   }
   ;

   /*
    * Integer(n)
    * constructs integer with value n
    */
   Integer(int n) {
      value = n;
   }

   /*
    * clone()
    * creates heap-allocated deep copy
    */
   Integer* clone() {
      return new Integer(value);
   }

   /*
    * static zero()
    * returns additive neutral element
    */
   static Integer* zero() {
      return new Integer(0);
   }

   /*
    * operator-()
    * returns additive inverse
    */
   Integer* operator-() {
      return new Integer(-value);
   }

   /*
    * operator+(other)
    * returns this + other
    */
   Integer* operator+(Integer *other) {
      return new Integer(value + other->value);
   }

   /*
    * operator*(other)
    * returns this*other
    */
   Integer* operator*(Integer *other) {
      return new Integer(value * other->value);
   }

   /*
    * operator==(other)
    * compares equality
    */
   bool operator==(Integer other) {
      return value == other.value;
   }

   /*
    * str()
    * returns string representation of Integer
    */
   string str() {
      return to_string(value);
   }
};

typedef RecPoly<Integer> UnivariatePoly;

typedef RecPoly<UnivariatePoly> BivariatePoly;

#endif /* TEMPLATERECURSIVE_H_ */
