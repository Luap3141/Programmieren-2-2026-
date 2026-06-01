#include <vector>
#include <string>
#include <exception>

using namespace std;

class Monomial {
	int coeff = 0;
	vector<int> powers = {};
public:
	Monomial() {};
	Monomial(int newCoeff, vector<int> newPowers);
	~Monomial() {}

	Monomial(const Monomial& other);
	Monomial& operator=(const Monomial& other);

	unsigned int length();

	static bool compare(const Monomial a, const Monomial b);

	const int operator[] (unsigned int i) const;
	int& operator[] (unsigned int i);

	const vector<int> exponents() const;
	vector<int>& exponents();
	int coefficient();
};

class DistPoly {
	int capacity = 10;
	int size = 0;
	int varNum = 0;
	string* varNames = nullptr;
	Monomial* terms = {};

public:
	DistPoly();

	DistPoly(int n; string* newVarNames)

	~DistPoly();
	DistPoly(const DistPoly& other);
	DistPoly& operator=(const DistPoly& other);

	void combineTerms();
	void reorder();
};
