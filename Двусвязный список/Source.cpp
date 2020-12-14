#include <iostream>
using namespace std;


template<typename T>
class DoublyList
{
public:
	DoublyList();
	~DoublyList();
	void push_back(T data);
	int GetSize()
	{
		return Size;
	}
	T& operator[](const int index);
	void pop_front();
	void clear();
	void push_front(T data);
	void insert(T data, int index);
	void removeAt(int index);
	void pop_back();

private:
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		Node* pPrev;
		T data;
		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
	};
	int Size;
	Node<T>* head;
	Node<T>* tail;
};




template<typename T>
DoublyList<T>::DoublyList()
{
	Size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
DoublyList<T>::~DoublyList()
{
	clear();
}

template<typename T>
void DoublyList<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else if (tail == nullptr)
	{
		tail = new Node<T>(data, nullptr, head); 
		head->pNext = tail;
	}
	else
	{
		Node<T>* current = tail;

		tail = new Node<T>(data, nullptr, tail);
		
		current->pNext = tail;
	}
	Size++;
}

template<typename T>
T& DoublyList<T>::operator[](const int index)
{
	

	if (Size / 2 >= index)
	{
		int counter = 0;

		Node<T>* current = this->head;

		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
	}
	else 
	{
		int counter = Size - 1;

		Node<T>* current = this->tail;

		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pPrev;
			counter--;
		}
	}

	
}

template<typename T>
void DoublyList<T>::pop_front()
{
	Node<T>* temp = head;

	head = head->pNext;

	delete temp;

	Size--;
}

template<typename T>
void DoublyList<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
void DoublyList<T>::push_front(T data)
{
	head = new Node<T>(data, head);
	Size++;
}

template<typename T>
void DoublyList<T>::insert(T data, int index)
{
	if (Size / 2 >= index)
	{
		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(data, previous->pNext, previous);

		Node<T>* current = previous->pNext;
		current->pPrev = newNode;

		previous->pNext = newNode;

		Size++;
	}
	else
	{
		Node<T>* next = this->tail;

		for (int i = Size; i > index + 1; i--)
		{
			next = next->pPrev;
		}

		Node<T>* newNode = new Node<T>(data, next, next->pPrev);

		Node<T>* current = next->pPrev;
		current->pNext = newNode;

		next->pPrev = newNode;

		Size++;
	}
}

template<typename T>
void DoublyList<T>::removeAt(int index)
{
	if (Size / 2 >= index)
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* toDelete = previous->pNext;

		previous->pNext = toDelete->pNext;

		Node<T>* next = toDelete->pNext;

		next->pPrev = previous;

		delete toDelete;

		Size--;
	}
	else
	{
		Node<T>* next = this->tail;

		for (int i = Size - 1; i > index + 1; i--)
		{
			next = next->pPrev;
		}

		

		Node<T>* toDelete = next->pPrev;

		next->pPrev = toDelete->pPrev;

		Node<T>* previous = toDelete->pPrev;

		previous->pNext = next;

		delete toDelete;

		Size--;
	}
}

template<typename T>
void DoublyList<T>::pop_back()
{
	Node<T>* temp = tail;

	tail = tail->pPrev;

	delete temp;

	Size--;
}

int main()
{
	
	DoublyList<int> lis;
	lis.push_back(0);
	lis.push_back(1);
	lis.push_back(2);
	lis.push_back(3);
	lis.push_back(4);
	lis.push_back(5);
	lis.push_back(6);
	lis.push_back(7);
	lis.push_back(8);
	lis.push_back(9);

	lis.insert(10, 7);
	//lis.removeAt(7);

	for (int i = 0; i < lis.GetSize(); i++)
	{
		cout << lis[i] << endl;
	}
	

	
	return 0;
}