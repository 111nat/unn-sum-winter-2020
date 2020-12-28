#include <iostream>
#include <string>
using namespace std;

typedef unsigned short WORD;

class Set
{
	int minElem;
	int maxElem;
	WORD* elems;
	int numWords;

	friend const Set& operator|(const Set& s1, const Set& s2);
	friend const Set& operator&(const Set& s1, const Set& s2);
	friend const Set& operator-(const Set& s1, const Set& s2);
	friend const Set& operator-(const Set& s);

public:
	Set(int min = 0, int max = 255);

	Set(const Set& s);

	~Set();

	bool Has(int n);

	Set& operator|=(int n);
	Set& operator|=(const Set& other);

	Set& operator&=(const Set& other);

	Set& operator-=(int n);
	Set& operator-=(const Set& other);

	Set& Inverse();
};

Set::Set(int min, int max)
{
	if (min > max)
	{
		minElem = max;
		maxElem = min;
	}
	else
	{
		minElem = min;
		maxElem = max;
	}
	int num = maxElem - minElem + 1;
	numWords = (num + 15) >> 4;
	elems = new WORD[numWords];

	for (int i = 0; i < numWords; i++)
	{
		elems[i] = 0;
	}
}

Set::Set(const Set& s)
{
	minElem = s.minElem;
	maxElem = s.maxElem;
	numWords = s.numWords;
	elems = new WORD[numWords];
	for (int i = 0; i < numWords; i++)
	{
		elems[i] = s.elems[i];
	}
}

Set::~Set()
{
	delete[] elems;
}

bool Set::Has(int n)
{
	if (n > maxElem || n < minElem)
	{
		return false;
	}
	else
	{
		int word = (n - minElem) >> 4;
		int bit = (n - minElem) & 15;
		return (elems[word] & (1 << bit)) != 0;
	}
}

Set& Set::operator|=(int n)
{
	if (n <= maxElem && n >= minElem)
	{
		int word = (n - minElem) >> 4;
		int bit = (n - minElem) & 15;
		elems[word] |= (1 << bit);
	}
	else
	{
		cout << "Error" << endl;
	}
	return *this;
}










int main()
{
	Set a;
	a |= 4;
	return 0;
}