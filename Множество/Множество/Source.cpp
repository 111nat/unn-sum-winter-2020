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

	/*friend const Set& operator|(const Set& s1, const Set& s2);
	friend const Set& operator&(const Set& s1, const Set& s2);
	friend const Set& operator-(const Set& s1, const Set& s2);
	friend const Set& operator-(const Set& s);*/

public:
	WORD getWord(int n);

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

WORD Set::getWord(int n)
{
	if (n < numWords && n > -1)
	{
		return elems[n];
	}
	else
	{
		cout << "error" << endl;
	}
}

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

Set& Set::operator|=(const Set& other)
{
	if (other.minElem != minElem || other.maxElem != maxElem)
	{
		cout << "Error" << endl;
	}
	else
	{
		for (int i = 0; i < numWords; i++)
		{
			elems[i] |= other.elems[i];
		}
	}
	return *this;
}

Set& Set::operator&=(const Set& other)
{
	if (other.minElem != minElem || other.maxElem != maxElem)
	{
		cout << "Error" << endl;
	}
	else
	{
		for (int i = 0; i < numWords; i++)
		{
			elems[i] &= other.elems[i];
		}
	}
	return *this;
}

Set& Set::operator-=(int n)
{
	if (n <= maxElem && n >= minElem)
	{
		int word = (n - minElem) >> 4;
		int bit = (n - minElem) & 15;
		elems[word] &= ~(1 << bit);
	}
	return *this;
}

Set& Set::operator-=(const Set& other)
{
	if (other.minElem != minElem || other.maxElem != maxElem)
	{
		cout << "error" << endl;
	}
	else
	{
		for (int i = 0; i < numWords; i++)
		{
			elems[i] &= ~other.elems[i];
		}
	}
	return *this;
}

Set& Set::Inverse()
{
	for (int i = 0; i < numWords; i++)
	{
		elems[i] = ~elems[i];
	}
	return *this;
}










void PrintSet(Set s)
{
	cout << "[";
	bool first = true;
	for (int i = 0; i < 256; i++)
	{
		if (s.Has(i))
		{
			cout << (first ? "" : ", ") << i;
			first = false;
		}
	}
	cout << "]" << endl;

}

int main()
{
	Set a;
	Set b;
	a |= 2;
	a |= 3;
	a |= 5;
	a |= 1;
	//a -= 1;
	PrintSet(a);
	PrintSet(a);
	cout<<a.getWord(0)<<endl;
	//unsigned short int s = 7;
	//s &= ~(1 << 2);
	//s &= 3;
	//cout << s;
	return 0;
}