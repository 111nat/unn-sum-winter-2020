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
	int size_words;
	Node* head;

public:
	hierarchy();
	void push_back(string data);
	string print_book(int book);
	string print_string(int book, int string);
	string print_word(int book, int stringg, int word);
	
};

hierarchy::hierarchy()
{
	size_book = 0;
	size_string = 0;
	size_words = 0;
	head = nullptr;
}

void hierarchy::push_back(string data)
{
	if (head == nullptr)
	{
		//Книги
		head = new Node(data);

		//Строки
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

		//Слова
		current = head->pDown;
		int size_wordss = 0;
		for (int i = 0; i < size_string; i++, current = current->pNext, size_wordss = 0)
		{
			Node* curentt = current;
			for (int k = 0; k < current->data.size();)
			{
				string stri = string();
				for (int j = k; j < current->data.size(); j++, k++)
				{

					if (current->data[j] != ' ')
					{
						stri.push_back(current->data[j]);
					}
					else
					{
						k++;
						j++;
						size_words++;
						size_wordss++;
						break;
					}

				}
				if (size_wordss == 1)
				{
					curentt->pDown = new Node(stri);
					curentt = curentt->pDown;
				}
				else
				{
					while (curentt->pNext != nullptr)
					{
						curentt = curentt->pNext;
					}
					curentt->pNext = new Node(stri);
				}
			}
		}
	}
	else
	{
		//Книги
		Node* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}

		current->pNext = new Node(data);

		//Строки

		Node* currentt = current->pNext;
		int size_stringg = 0;

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
					size_stringg++;
					break;
				}
			}
			if (size_stringg == 1)
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

		//Слова
		current = head;
		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current = current->pDown;
		
		int size_wordss = 0;
		for (int i = 0; i < size_stringg; i++, current = current->pNext, size_wordss = 0)
		{
			Node* curentt = current;
			for (int k = 0; k < current->data.size();)
			{
				string stri = string();
				for (int j = k; j < current->data.size(); j++, k++)
				{

					if (current->data[j] != ' ')
					{
						stri.push_back(current->data[j]);
					}
					else
					{
						k++;
						j++;
						size_words++;
						size_wordss++;
						break;
					}

				}
				if (size_wordss == 1)
				{
					curentt->pDown = new Node(stri);
					curentt = curentt->pDown;
				}
				else
				{
					while (curentt->pNext != nullptr)
					{
						curentt = curentt->pNext;
					}
					curentt->pNext = new Node(stri);
				}
			}
		}
	}
	size_book++;
}

string hierarchy::print_book(int book)
{
	if (book > size_book)
	{
		cout << "Ошибка! Книг меньше." << endl;
		cout << "Всего книг: " << size_book << endl;
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
	return string();
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
			int counter_b = 1;
			int counter_s = 1;
			Node* current = this->head;

			while (current != nullptr)
			{
				if (counter_b == book)
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
				counter_b++;
			}
			cout << "Ошибка! Глава не найдена" << endl;
		}
	}
	return string();
}

string hierarchy::print_word(int book, int stringg, int word)
{
	if (book > size_book)
	{
		cout << "Ошибка! Книг меньше." << endl;
		cout << "Всего Книг: " << size_book << endl;
	}
	else
	{


		int counter_b = 1;
		int counter_s = 1;
		int counter_w = 1;
		Node* current = this->head;

		while (current != nullptr)
		{
			if (counter_b == book)
			{
				current = current->pDown;
				while (current != nullptr)
				{
					if (counter_s == stringg)
					{
						int amount_of_words = 0;
						for (int i = 0; i < current->data.size(); i++)
						{
							if (current->data[i] == ' ')
							{
								amount_of_words++;
							}
						}
						amount_of_words++;
						current = current->pDown;
						while (current != nullptr)
						{
							if (counter_w == word)
							{
								cout << current->data << endl;
								return current->data;
							}
							current = current->pNext;
							counter_w++;
						}
						cout << "Ошибка! Слово не найдено" << endl;
						cout << "Всего слов: " << amount_of_words << endl;
						return string();
					}
					current = current->pNext;
					counter_s++;
				}
				cout << "Ошибка! Строка не найдена" << endl;
				return string();
			}
			current = current->pNext;
			counter_b++;
		}
	}
	return string();
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
		int choose, index_f, index_s, index_t;
		cout << "1. print book. (index book)" << endl;
		cout << "2. print string. (index book, index string)" << endl;
		cout << "3. print word. (index book, index string, index word)" << endl;
		cout << "4. more books." << endl;
		cout << "0. Exit." << endl;
		cin >> choose;
		switch (choose)
		{
			case 1:
				system("cls");
				cout << "Enter index of book" << endl;
				cin >> index_f;
				list.print_book(index_f);
				break;
			case 2:
				system("cls");
				cout << "Enter index of book and index of string" << endl;
				cin >> index_f;
				cin >> index_s;
				list.print_string(index_f, index_s);
				break;
			case 3:
				system("cls");
				cout << "Enter index of book and index of string and index of word" << endl;
				cin >> index_f;
				cin >> index_s; 
				cin >> index_t;
				list.print_word(index_f, index_s, index_t);
				break;
			case 4:
				plus_books();
				break;
			case 0:
				Exit = 0;
				break;
			default:
				continue;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	work_with_hierarchy();
	
	return 0;
}


