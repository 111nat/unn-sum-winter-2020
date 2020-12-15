#include <iostream>
#include <fstream>
using namespace std;

string open_file()
{
	ifstream harry_1;
	harry_1.open("Harry_Potter_1.txt");
	string book = string();

	if (!harry_1.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		cout << "Файл открыт!" << endl;
		
		char ch;
		while (harry_1.get(ch))
		{
			book.push_back(ch);
		}
	}
	
	harry_1.close();
	return book;
}

class hierarchy
{
	class Node
	{
	public:
		Node* pNext;
		Node* pDown;
		string data;

		Node(string data = string(), Node* pNext = nullptr, Node* pDown = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pDown = pDown;
		}
	};

	int size_chapter;
	Node* head;

public:
	hierarchy();
	void push_back(string data);
};

hierarchy::hierarchy()
{
	size_chapter = 0;
	head = nullptr;
}

void hierarchy::push_back(string data)
{
	if (head == nullptr)
	{
		head = new Node(data);
	}
}










int main()
{
	setlocale(LC_ALL, "ru");
	
	return 0;
}


