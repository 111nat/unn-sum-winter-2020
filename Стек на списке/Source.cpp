#include <iostream>
using namespace std;

template<typename T>
class List
{
public:
	List();
	~List();
	
	int GetSize()
	{
		return Size;
	}
	
	T pop_front();
	void clear();
	void push_front(T data);
	
	void print();
private:
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		T data;
		Node(T data = T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	int Size;
	Node<T>* head;
};

template<typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
T List<T>::pop_front()
{
	if (head != nullptr)
	{
		T savior = head->data;

		Node<T>* temp = head;
		
		head = head->pNext;

		delete temp;

		Size--;
		
		return savior;
	}
	else {
		cout << "Stack is empty" << endl;
		return T();
	}
}

template<typename T>
void List<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
void List<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	Size++;
}

template<typename T>
void List<T>::print()
{
	Node<T>* temp = head;

	for (int i = 0; i < Size; i++) {
		cout << temp->data << endl;
		temp = temp->pNext;
	}
	
	
}






int main()
{
	List<int> lst;
	lst.push_front(1);
	lst.push_front(2);
	lst.push_front(3);
	lst.push_front(4);
	cout << lst.GetSize() << endl;
	cout << lst.pop_front() << endl;
	cout << "xd" << endl;
	lst.print();




	return 0;
}