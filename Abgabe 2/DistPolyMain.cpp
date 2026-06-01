#include "DistPoly.h"
#include <iostream>
#include <vector>
#include <random>

using namespace std;

int main() {
	//My tests
	//rng stuff
	default_random_engine rng;
	random_device rand_dev;
	rng.seed(rand_dev());
	uniform_int_distribution<int> next_r(0,10);

	Monomial M_a[10];
	Monomial M_b[10];
	for (int i = 0; i < 10; i++) {
		vector<int> a = {next_r(rng),next_r(rng),next_r(rng)};
		vector<int> b = {next_r(rng),next_r(rng),next_r(rng)};
		M_a[i] = Monomial(next_r(rng),a);
		M_b[i] = Monomial(next_r(rng),b);
	}

	DistPoly A(10,10,{"x","y","z"}, M_a);
	DistPoly B(10,10,{"x","y","z"}, M_b);

	A.reorder();
	B.reorder();
	cout << "Here";

	//Skeleton Code
	// some exponent vectors ("power products")
	int e1[2] = {1,2}; int e2[2] = {2,1}; int e3[2] = {1,0};
	int e4[2] = {0,1}; int e5[2] = {0,0}; int e6[2] = {2,2};
	// construct zero polynomial in two variables, then add monomials
	string vars[2] = {"x","y"};
	DistPoly p(2, vars);
	p.add(3,e1).add(5,e2).add(7,e3).add(11,e4).add(13,e5);
	// construct zero polynomial in two variables, then add monomials
	DistPoly q(2, vars);
	q.add(11,e4).add(-3,e2).add(2,e6).add(-2,e2);
	// print p and q
	cout << p.str() << endl;
	cout << q.str() << endl;
	// set p to p+2*q and print it
	DistPoly r = p;
	r.add(q).add(q);
	p = r;
	cout << p.str() << endl;
	return 0;
}
