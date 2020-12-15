#include <iostream>
#include <fstream>
using namespace std;

string open_file(string path)
{
	ifstream harry_1;
	harry_1.open(path);
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

	int size_book;
	int size_string;
	Node* head;

public:
	hierarchy();
	int Get_size_book()
	{
		return size_book;
	};
	int Get_size_string()
	{
		return size_string;
	};
	void push_back(string data);
	string print_book(int book);
	string print_string(int book, int string);
	
};

hierarchy::hierarchy()
{
	size_book = 0;
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
	else
	{
		Node* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}

		current->pNext = new Node(data);

		Node* currentt = current->pNext;


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
				currentt->pDown = new Node(stri);
				currentt = currentt->pDown;
			}
			else
			{
				while (currentt->pNext != nullptr)
				{
					currentt = currentt->pNext;
				}
				currentt->pNext = new Node(stri);
			}
		}
	}
	size_book++;
}

string hierarchy::print_book(int book)
{
	if (book > size_book)
	{
		cout << "Ошибка! Глав меньше." << endl;
		cout << "Всего глав: " << size_book << endl;
	}
	else
	{
		int counter = 1;
		Node* current = this->head;
		while (current != nullptr)
		{
			if (counter == book)
			{
				cout << current->data << endl;
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
		cout << "Ошибка! Глава не найдена" << endl;
	}
}

string hierarchy::print_string(int book, int stringg)
{
	if (book > size_book)
	{
		cout << "Ошибка! Книг меньше." << endl;
		cout << "Всего Книг: " << size_book << endl;
	}
	else
	{
		if (stringg > size_string)
		{
			cout << "Ошибка! Строк меньше." << endl;
			cout << "Всего строк: " << size_string << endl;
		}
		else
		{
			int counter_c = 1;
			int counter_s = 1;
			Node* current = this->head;

			while (current != nullptr)
			{
				if (counter_c == book)
				{
					current = current->pDown;
					while (current != nullptr)
					{
						if (counter_s == stringg)
						{
							cout << current->data << endl;
							return current->data;
						}
						current = current->pNext;
						counter_s++;
					}
					cout << "Ошибка! Строка не найдена" << endl;
					return string();
				}
				current = current->pNext;
				counter_c++;
			}
			cout << "Ошибка! Глава не найдена" << endl;
		}
	}
}










hierarchy list;

void plus_books()
{
	string PATH = string();
	cout << "Введите книгу .txt" << endl;
	cin >> PATH;
	PATH = PATH + ".txt";
	
	if (open_file(PATH) != string())
	{
		list.push_back(open_file(PATH));
	}
}

void work_with_hierarchy()
{
	int Exit = 1;
	while (Exit)
	{
		cout << endl << endl;
		int choose;
		cout << "1. print book. (index book)" << endl;
		cout << "2. print string. (index book, index string)" << endl;
		cout << "0. Exit." << endl;
		cin >> choose;
		switch (choose)
		{
			case 1:
				system("cls");
				int index;
				cout << "Enter index of book" << endl;
				cin >> index;
				list.print_book(index);
				break;
			case 2:
				system("cls");
				int index_f, index_s;
				cout << "Enter index of book and index of string" << endl;
				cin >> index_f;
				cin >> index_s;
				list.print_string(index_f, index_s);
				break;
			case 0:
				Exit = 0;
				break;
			default:
				break;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	int exit = 1;
	int counter = 0;
	
	while (exit)
	{
		if (counter == 0)
		{
			if (open_file("HP.txt") != string())
			{
				cout << "Найден HP" << endl;
				cout << "Продолжим?" << endl;
				cout << "1 for yes   or   0 for no" << endl;
				cin >> exit;
				if (exit != 0 && exit != 1)
				{
					exit = 0;
					cout << "Значит нет" << endl;
				}
			}
			counter++;
		}

		plus_books();
		cout << endl;
		cout << "Нужно больше книг?" << endl;
		cout << "1 for yes   or   0 for no" << endl;
		cin >> exit;
		if (exit != 0 && exit != 1)
		{
			exit = 0;
			cout << "Значит нет" << endl;
		}
	}
	
	work_with_hierarchy();
	
	return 0;
}


