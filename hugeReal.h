#pragma once
#include<iostream>
using namespace std;
class hugeReal
{
	int* Ds;
	int pos, size;
	bool isNeg;
	static int base;

	void strToReal(const string& num);
	void shrink();
	void deepCopy(const hugeReal& R);
	void shiftLeft();
	hugeReal QwiseAdd(const hugeReal& N2)const;
	hugeReal QwiseSub(const hugeReal& N2)const;
	bool QwiseGreat(const hugeReal& N2)const;
	bool QwiseLess(const hugeReal& N2)const;
	bool QwiseEqual(const hugeReal& N2)const;

public:
	hugeReal(int s = 0, int p = 0);
	hugeReal(const hugeReal& N);
	hugeReal(const string& num);
	hugeReal(istream& rdr);
	const hugeReal& operator=(const hugeReal& N);

	
	static void setBase(int b) { hugeReal::base = b; }
	static int getBase() { return hugeReal::base; }
	bool operator>(const hugeReal& N2)const;
	bool operator>=(const hugeReal& N2)const;
	bool operator<(const hugeReal& N2)const;
	bool operator<=(const hugeReal& N2)const;
	bool operator==(const hugeReal& N2)const;
	bool operator!=(const hugeReal& N2)const;

	hugeReal operator+(const hugeReal& N2)const;
	hugeReal operator+=(const hugeReal& N2);
	hugeReal operator-(const hugeReal& N2)const;
	hugeReal operator-=(const hugeReal& N2);
	hugeReal operator*(const hugeReal& N2)const;
	const hugeReal& operator*=(const hugeReal& N2);
	hugeReal operator/(const hugeReal& N2)const;
	const hugeReal& operator/=(const hugeReal& N2);
	hugeReal operator-()const;

	hugeReal& operator++();
	hugeReal& operator--();
	hugeReal operator++(int);
	hugeReal operator--(int);


	int operator()(int i, int ind)const;
	int& operator()(int i, int ind);
	
	friend istream& operator >>(istream& in, hugeReal& R);
	friend ostream& operator<<(ostream& out, const hugeReal& R);
};

