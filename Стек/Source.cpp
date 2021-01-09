#include <iostream>
using namespace std;

template <typename T>
class Stack
{
public:
	Stack(int size);
	~Stack();

	void Push(T data);
	void pop();
	T Top();
	bool isEmpty();
	bool isFull();
	void print();
private:
	T* arr;
	int Size;
	int top;
};

template<typename T>
Stack<T>::Stack(int size)
{
	arr = new T[size];
	top = -1;
	Size = size;
}

template<typename T>
Stack<T>::~Stack()
{
	delete[] arr;
}

template<typename T>
void Stack<T>::Push(T data)
{
	if (top != Size - 1)
	{
		top++;
		arr[top] = data;
	}
	else {
		cout << "Stack is full" << endl;
	}
}

template<typename T>
void Stack<T>::pop()
{
	if (top != -1)
	{
		int _top = top;
		top--;
		
	}
	else {
		cout << "Stack is empty" << endl;
	}
	
}

template<typename T>
T Stack<T>::Top()
{
	if (top != -1)
	{
		return arr[top];
	}
	else
	{
		cout << "Stack is empty" << endl;
		return T();
	}
}

template<typename T>
bool Stack<T>::isEmpty()
{
	if (top == -1)
	{
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
bool Stack<T>::isFull()
{
	if (top == Size - 1)
	{
		return true;
	}
	else {
		return false;
	}
}

template<typename T>
void Stack<T>::print()
{
	int _top = top;
	while (_top != -1) {
		cout << arr[_top] << endl;
		_top--;
	}
}

int main()
{
	Stack<int> sta(5);
	sta.Push(1);
	sta.Push(2);
	sta.Push(3);
	sta.Push(4);
	sta.Push(5);
	sta.print();
	cout << endl;
	cout << sta.isEmpty() << endl;
	cout << sta.isFull() << endl;
	cout << sta.Top() << endl;
	cout << endl;
	sta.pop();
	sta.print();
	cout << endl;
	sta.pop();
	sta.pop();
	sta.pop();
	sta.pop();
	cout << sta.isEmpty() << endl;
	cout << sta.isFull() << endl;
	cout << sta.Top() << endl;
	sta.pop();
	return 0;
}