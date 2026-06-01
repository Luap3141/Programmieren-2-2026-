#include "DistPoly.h"
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>

Monomial::Monomial(int newCoeff, vector<int> newPowers) {
	coeff = newCoeff;
	powers = newPowers;
}

Monomial::Monomial(const Monomial& other) {
	coeff = other.coeff;
	powers = other.powers;
}

Monomial& Monomial::operator= (const Monomial& other) {
	coeff = other.coeff;
	powers = other.powers;
	return *this;
}

const int Monomial::operator[] (unsigned int i) const {
	if (i == 0) {
		return coeff;
	}
	if (i > powers.size()) {
		throw 123;
	}
	return powers[i-1];
}
int& Monomial::operator[] (unsigned int i) {
	if (i == 0) {
		return coeff;
	}
	if (i > powers.size()) {
		throw 123;
	}
	return powers[i-1];
}

const std::vector<int> Monomial::exponents() const {
	return powers;
}

std::vector<int>& Monomial::exponents() {
	return powers;
}

unsigned int Monomial::length() {
	return powers.size();
}

int Monomial::coefficient() {
	return coeff;
}

bool Monomial::compare(const Monomial a, const Monomial b) {
	for (unsigned int i = 0; i < a.powers.size(); i++) {
		if (a.powers[i] < b.powers[i]) {
			return true;
		}
		if (a.powers[i] > b.powers[i]) {
			return false;
		}
	}

	return false;
}

DistPoly::DistPoly() {};
/*

DistPoly::DistPoly(int newCapacity, int newSize, vector<string> newVarNames, Monomial* newTerms) {
	for (int i = 0; i < newSize; i++) {
		if(newVarNames.size() != newTerms[i].length()) {
			throw "Mismatch betwwen amount of variables and length of monomials";
		}
	}
	capacity = newCapacity;
	size = newSize;
	varNames = newVarNames;
	terms = new Monomial[newSize];
	for (int i = 0; i < newSize; i++) {
		terms[i] = newTerms[i];
	}
}
*/

DistPoly::~DistPoly() {
	delete[] terms;
	delete[] varNames;
}

DistPoly::DistPoly(const DistPoly& other) {
	capacity = other.capacity;
	size = other.size;

	varNames = other.varNames;

	terms = new Monomial[capacity];
	for (int i = 0; i < size; i++) {
		terms[i] = other.terms[i];
	}
}

DistPoly& DistPoly::operator= (const DistPoly& other) {
	capacity = other.capacity;
	size = other.size;

	varNames = other.varNames;

	terms = new Monomial[capacity];
	for (int i = 0; i < size; i++) {
		terms[i] = other.terms[i];
	}
	return *this;
}

//TODO: Optimize these two later

void DistPoly::combineTerms() {
	Monomial myTerms[size];
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < i + 1; j++) {
			if (myTerms[j].exponents() == terms[i].exponents()) {
				terms[j][0] += terms[i][0];
				break;
			}
			if (j==i) {
				myTerms[i] = terms[i];
			}
		}
	}
}

void DistPoly::reorder() {
	combineTerms();
	std::sort(terms,terms+size,Monomial::compare);
}
