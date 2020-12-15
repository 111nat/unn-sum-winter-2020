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
		cout << "������ �������� �����!" << endl;
	}
	else
	{
		cout << "���� ������!" << endl;
		
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
	int size_string;
	Node* head;

public:
	hierarchy();
	void push_back(string data);
	void print_chapter(int chapter);
	void print_string(int chapter, int string);
};

hierarchy::hierarchy()
{
	size_chapter = 0;
	size_string = 0;
	head = nullptr;
}

void hierarchy::push_back(string data)
{
	if (head == nullptr)
	{
		head = new Node(data);

		Node* current = head;
		

		for (int i = 0; i < data.size();)
		{
			string stri = string();
			for (int j = i; j < data.size(); j++, i++)
			{
				if (data[j] != '\n')
				{
					stri.push_back(data[j]);
				}
				else
				{
					i++;
					j++;
					size_string++;
					break;
				}
			}
			if (size_string == 1)
			{
				current->pDown = new Node(stri);
				current = current->pDown;
			}
			else
			{
				while (current->pNext != nullptr)
				{
					current = current->pNext;
				}
				current->pNext = new Node(stri);
			}
		}
		
	}
	size_chapter++;
}

void hierarchy::print_chapter(int chapter)
{
	if (chapter > size_chapter)
	{
		cout << "������! ���� ������." << endl;
		cout << "����� ����: " << size_chapter << endl;
	}
	else
	{
		int counter = 1;
		Node* current = this->head;
		while (current != nullptr)
		{
			if (counter == chapter)
			{
				cout << current->data << endl;
				return void();
			}
			current = current->pNext;
			counter++;
		}
		cout << "������! ����� �� �������" << endl;
	}
}

void hierarchy::print_string(int chapter, int string)
{
	if (chapter > size_chapter)
	{
		cout << "������! ���� ������." << endl;
		cout << "����� ����: " << size_chapter << endl;
	}
	else
	{
		if (string > size_string)
		{
			cout << "������! ����� ������." << endl;
			cout << "����� �����: " << size_string << endl;
		}
		else
		{
			int counter_c = 1;
			int counter_s = 1;
			Node* current = this->head;

			while (current != nullptr)
			{
				if (counter_c == chapter)
				{
					current = current->pDown;
					while (current != nullptr)
					{
						if (counter_s == string)
						{
							cout << current->data << endl;
							return void();
						}
						current = current->pNext;
						counter_s++;
					}
					cout << "������! ������ �� �������" << endl;
					return void();
				}
				current = current->pNext;
				counter_c++;
			}
			cout << "������! ����� �� �������" << endl;
		}
	}
}










int main()
{
	setlocale(LC_ALL, "ru");
	hierarchy first;
	first.push_back(open_file());
	first.print_string(1, 5);
	
	return 0;
}


