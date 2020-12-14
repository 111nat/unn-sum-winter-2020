#include <iostream>
using namespace std;

template<typename T>
class queue
{
public:
	queue();
	~queue();
	void push_back(T data);
	int GetSize()
	{
		return size;
	}
	T Top();
	T Back();
	void pop_front();
	void clear();
	bool isEmpty();

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

	int size;
	Node<T>* head;
	Node<T>* tail;
};

template<typename T>
queue<T>::queue()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
queue<T>::~queue()
{
	clear();
}

template<typename T>
void queue<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else if (tail == nullptr)
	{
		tail = new Node<T>(data);
		head->pNext = tail;
	}
	else
	{
		Node<T>* current = tail;
		tail = new Node<T>(data);
		current->pNext = tail;
	}
	size++;
}

template<typename T>
T queue<T>::Top()
{
	return head->data;
}

template<typename T>
T queue<T>::Back()
{
	return tail->data;
}

template<typename T>
void queue<T>::pop_front()
{
	Node<T>* temp = head;

	head = head->pNext;

	delete temp;

	size--;
}

template<typename T>
void queue<T>::clear()
{
	while (size)
	{
		pop_front();
	}
}

template<typename T>
bool queue<T>::isEmpty()
{
	if (size > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
	
}

int main()
{
	queue<int> que;
	que.push_back(1);
	que.push_back(2);
	que.push_back(3);
	que.push_back(4);
	que.push_back(5);
	cout << que.GetSize() << endl;
	cout << "top: " << que.Top() << endl;
	cout << "back: " << que.Back() << endl;
	que.pop_front();
	cout << "top: " << que.Top() << endl;
	cout << "back: " << que.Back() << endl;
	cout << que.GetSize() << endl;
	que.clear();
	cout << que.isEmpty() << endl;
	return 0;
}