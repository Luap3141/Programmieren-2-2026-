/*
 * DistPoly.h
 *
 *  Created on: Apr 23, 2026
 *      Author: luap314
 */

#include <string>

using namespace std;

class Monomial {
	int coeff = 0;
	unsigned int length = 0;
	int *exponents = nullptr;

public:

	//Constructors and destructor, copy constructor and copy assignment operator
	Monomial(int newCoeff, unsigned int newLength, int *newExponents);
	Monomial() {};
	~Monomial() {delete[] exponents;}
	Monomial(const Monomial &other);
	Monomial& operator=(const Monomial &other);

/*
 * static bool compare(a,b)
 * a and b need to be Monomials of the same size.
 * returns true if, lexicographically based on the exponents, a is greater than b
 * false otherwise.
 */

	static bool compare(const Monomial &a, const Monomial &b);

/*
 * static bool sameExp(a,b)
 * a and b need to be Monomials of the same size.
 * returns true if the exponents are the same
 */
	static bool sameExp(const Monomial &a, const Monomial &b);

/*
 * void setCoeff
 * allows non-members to change the coefficient of a Monomial
 */
	void setCoeff(int newCoeff) {
		coeff = newCoeff;
	}

/*
 * int getCoeff
 * allows non-members to see the coefficient of a Monomial
 */
	int getCoeff() {
		return coeff;
	}

/*
 * unsigned int getLength
 * allows non-members to see the length of a Monomial
 */
	unsigned int getLength() {
		return length;
	}

/*
 * str(varNames)
 * varNames is an array of strings. the Length of that array needs to be
 * the same as the length of the Monomial.
 * returns a string in the form of
 * ax^1y^2z^3 and so on.
 *
 * returns 0 if the length or the coefficient are 0.
 * doesn't concatenate variables with exponent 0 to the Output.
 */

	string str(string *varNames);
};

class DistPoly {

	unsigned int capacity = 10;
	unsigned int size = 0;
	unsigned int varNum = 2;
	string *varNames = nullptr;
	Monomial *terms = { };

public:
	// zero-polynomial in n variables with given names
	DistPoly(int n, string *vars);
	// copy constructor, copy assignment operator, destructor
	DistPoly(DistPoly &p);
	DistPoly& operator=(const DistPoly &p);
	~DistPoly();
	// add new term with given coefficient and exponents to this polynomial
	// and return this polynomial

/*
 * increases capacity by 2n+1.
 * needed when size gets close to capacity.
 */
	void resize();

/*
 * DistPoly add(Summand)
 * adds a Monomial to the Polynomial.
 * Summand needs to be the same size as varNum
 */
	DistPoly& add(Monomial Summand);

/*
 * DistPoly add(newCoeff,newExponents)
 * creates a monomial and adds it.
 * Length of newExponents needs to match Amount of Variables.
 */
	DistPoly& add(int newCoeff, int *newExponents);
	// add polynomial p to this polynomial and return this polynomial
	DistPoly& add(DistPoly &p);
	// the string representation of this polynomial
	string str();

/*
 * void removeAt(index)
 * removes one Term and moves all the others accordingly.
 * index needs to be in range
 */
	void removeAt(unsigned int index);

/*
 * void sanitize()
 * returns Polynomial to canonical Form.
 * Terms with 0 will be removed.
 * Reverse Lexicographical order for the terms
 * and same exponent terms get combined
 */
	void sanitize();

/*
 * void removeZeroes()
 * Removes all Terms with coefficient 0
 */
	void removeZeroes();

/*
 * void combineTerms()
 * combines terms with same exponent b adding their coefficients
 * only works, when reorder has been called previously.
 */
	void combineTerms(unsigned int start);

/*
 * void reorder()
 * Orders the Terms of a polynomial in reverse lexicographical order.
 */
	void reorder();
};
