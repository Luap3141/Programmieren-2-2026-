/*
 * DistPoly.cpp
 *
 *  Created on: Apr 23, 2026
 *      Author: luap314
 */

#include "DistPoly.h"
#include <string>
#include <iostream>
#include <algorithm>
#include <stdexcept>

Monomial::Monomial(int newCoeff, unsigned int newLength, int *newExponents) {
   coeff = newCoeff;
   length = newLength;
   exponents = new int[length];

   for (unsigned int i = 0; i < newLength; i++) {
      exponents[i] = newExponents[i];
   }
}

bool Monomial::sameExp(const Monomial &a, const Monomial &b) {
   if (a.length != b.length) {
      return false;
   }

   for (unsigned int i = 0; i < a.length; i++) {
      if (a.exponents[i] != b.exponents[i]) {
         return false;
      }
   }
   return true;
}

bool Monomial::compare(const Monomial &a, const Monomial &b) {
   if (a.length != b.length) {
      throw std::range_error("Cannot compare Monomials of different sizes");
   }

   for (unsigned int i = 0; i < a.length; i++) {
      if (a.exponents[i] > b.exponents[i]) {
         return true;
      }
      if (a.exponents[i] < b.exponents[i]) {
         return false;
      }
   }
   return false;
}

string Monomial::str(string *varNames) {
   if (length == 0 || coeff == 0) {
      return "0";
   }
   string Output = std::to_string(coeff);
   for (unsigned int i = 0; i < length; i++) {
      if (exponents[i] != 0) {
         Output += varNames[i] + "^" + std::to_string(exponents[i]);
      }
   }
   return Output;
}

Monomial::Monomial(const Monomial &other) {
   coeff = other.coeff;
   length = other.length;
   exponents = new int[length];
   for (unsigned int i = 0; i < length; i++) {
      exponents[i] = other.exponents[i];
   }
}
Monomial& Monomial::operator=(const Monomial &other) {
   /*if (this == &other) {return *this;};
    coeff = other.coeff;
    length = other.length;

    delete[] exponents;

    exponents = new int[length];
    for (unsigned int i = 0; i < length; i++) {
    exponents[i] = other.exponents[i];
    }
    return *this;*/
   if (this == &other)
      return *this;

   delete[] exponents;  // free old memory

   coeff = other.coeff;
   length = other.length;

   if (length > 0) {
      exponents = new int[length];
      for (unsigned int i = 0; i < length; i++) {
         exponents[i] = other.exponents[i];
      }
   } else {
      exponents = nullptr;
   }

   return *this;
}

DistPoly::DistPoly(int n, string *vars) {
   varNum = n;
   varNames = new string[n];
   for (int i = 0; i < n; i++) {
      varNames[i] = vars[i];
   }
   capacity = 10;
   size = 0;
   terms = new Monomial[capacity];
}

DistPoly::DistPoly(DistPoly &p) {
   capacity = p.capacity;
   size = p.size;
   varNum = p.varNum;

   terms = new Monomial[capacity];
   for (unsigned int i = 0; i < size; i++) {
      terms[i] = p.terms[i];
   }
   varNames = new string[varNum];
   for (unsigned int i = 0; i < varNum; i++) {
      varNames[i] = p.varNames[i];
   }
}

DistPoly& DistPoly::operator=(const DistPoly &p) {
   if (this == &p)
      return *this;

   delete[] terms;
   delete[] varNames;

   capacity = p.capacity;
   size = p.size;
   varNum = p.varNum;

   terms = new Monomial[capacity];
   for (unsigned int i = 0; i < size; i++) {
      terms[i] = p.terms[i];
   }

   varNames = new string[varNum];
   for (unsigned int i = 0; i < varNum; i++) {
      varNames[i] = p.varNames[i];
   }

   return *this;
}

DistPoly::~DistPoly() {
   delete[] terms;
   delete[] varNames;
}

void DistPoly::resize() {
   unsigned int newCapacity = 2 * capacity + 1;
   Monomial *newTerms = new Monomial[newCapacity];
   for (unsigned int i = 0; i < size; i++) {
      newTerms[i] = terms[i];
   }
   delete[] terms;
   terms = newTerms;
   capacity = newCapacity;
}

DistPoly& DistPoly::add(Monomial Summand) {
   if (varNum != Summand.getLength()) {
      throw std::range_error("Cannot add wrong-sized Monomial");
   }
   if (size == capacity) {
      resize();
   }
   terms[size] = Summand;
   size++;
   sanitize();
   return *this;
}

DistPoly& DistPoly::add(int newCoeff, int *newExponents) {
   add(Monomial(newCoeff, varNum, newExponents));
   return *this;
}

DistPoly& DistPoly::add(DistPoly &p) {

   for (unsigned int i = 0; i < p.size; i++) {
      add(p.terms[i]);
   }
   return *this;
}

string DistPoly::str() {
   if (size == 0) {
      return "0";
   }

   string Output = "";
   for (unsigned int i = 0; i < size - 1; i++) {
      Output += terms[i].str(varNames) + " + ";
   }
   Output += terms[size - 1].str(varNames);
   return Output;
}

void DistPoly::removeAt(unsigned int index) {
   if (index >= size) {
      throw std::out_of_range("Index out of bounds");
   }

   for (unsigned int i = index; i < size - 1; i++) {
      terms[i] = terms[i + 1];
   }

   size--; // just shrink logical size
}

void DistPoly::reorder() {
   std::sort(terms, terms + size, Monomial::compare);
}

void DistPoly::combineTerms(unsigned int start) {
   //Note:: Only use when reorder has been used before
   if (start >= size - 1) {
      return;
   }
   if (Monomial::sameExp(terms[start], terms[start + 1])) {
      terms[start].setCoeff(
            terms[start].getCoeff() + terms[start + 1].getCoeff());
      removeAt(start + 1);
      combineTerms(start);
   }
   combineTerms(start + 1);

}

void DistPoly::removeZeroes() {
   unsigned int i = 0;
   while (i < size) {
      if (terms[i].getCoeff() == 0) {
         removeAt(i);
      } else {
         i++;
      }
   }
}

void DistPoly::sanitize() {
   reorder();
   combineTerms(0);
   removeZeroes();
}

