#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

stack<string> names;

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
		names.push(path);
		char ch;
		while (harry_1.get(ch))
		{
			book.push_back(ch);
		}
	}
	
	harry_1.close();
	return book;
}

void open_file_rewrite(string new_string, int index_b)
{
	stack<string> right_names;
	stack<string> helper;
	while (!names.empty())
	{
		right_names.push(names.top());
		helper.push(names.top());
		names.pop();

	}

	while (!helper.empty())
	{
		names.push(helper.top());
		helper.pop();
	}

	int counter = 1;
	string path = string();
	while (!right_names.empty())
	{
		if (counter == index_b)
		{
			path = right_names.top();
			break;
		}
		counter++;
		right_names.pop();
	}

	ofstream file;
	file.open(path);
	if (!file.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		file << new_string;
		file << ' ';
		file << "\n";
	}
	file.close();
	return void();
}

void open_file_add(string new_string, int index_b)
{
	stack<string> right_names;
	stack<string> helper;
	while (!names.empty())
	{
		right_names.push(names.top());
		helper.push(names.top());
		names.pop();

	}

	while (!helper.empty())
	{
		names.push(helper.top());
		helper.pop();
	}

	int counter = 1;
	string path = string();
	while (!right_names.empty())
	{
		if (counter == index_b)
		{
			path = right_names.top();
			break;
		}
		counter++;
		right_names.pop();
	}

	ofstream file;
	file.open(path, ofstream::app);
	if (!file.is_open())
	{
		cout << "Ошибка открытия файла!" << endl;
	}
	else
	{
		
		file << new_string;
		file << ' ';
		file << "\n";
	}
	file.close();
	return void();
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

	int get_size_books()
	{
		return size_book;
	}

	int get_size_string(int index_book)
	{
		Node* curent = head;
		int counter = 1;
		while (curent->pNext != nullptr)
		{
			if (counter == index_book)
			{
				if (curent->pDown != nullptr)
				{
					curent = curent->pDown;
					int new_counter = 1;
					while (curent->pNext != nullptr)
					{
						new_counter++;
						curent = curent->pNext;
					}
					cout << "Кол-во строк: " << new_counter << "В книги: " << index_book << endl;
					return new_counter;
				}
				else
				{
					cout << "Строк не найдено" << endl;
					return int();
				}
			}
			curent = curent->pNext;
			counter++;
		}
		cout << "Error" << endl;
		return int();
	}

	void changer_book(int index_book);
	void changer_string(int index_book, int index_string);
	void changer_word(int index_book, int index_string, int index_word);
	
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

void hierarchy::changer_book(int index_book)
{
	Node* searcher = head;
	int counter = 1;
	while (searcher != nullptr)
	{
		if (counter == index_book)
		{
			string new_book = string();
			cout << "Enter new book." << endl;
			cin >> new_book;
			open_file_rewrite(new_book, index_book);
			int choose = 0;
			while (1) {
				cout << "Хотите продолжить на новой строке" << endl;
				cout << "1 or 0" << endl;

				cin >> choose;
				if (choose == 1)
				{
					cout << "Enter continuation." << endl;
					new_book = string();
					cin >> new_book;
					open_file_add(new_book, index_book);
				}
				else
				{
					Node* deleter = searcher;
					Node* helper1 = searcher;
					int counter1 = 0;
					while (1)
					{
						if (searcher->pDown == nullptr)
						{
							break;
						}
						while (deleter->pDown != nullptr)
						{
							
							
							deleter = deleter->pDown;
							if (deleter->pDown != nullptr)
							{
								helper1 = helper1->pDown;
							}
						}
						
						while (deleter->pNext != nullptr)
						{
							
							if (counter1 == 0)
							{
								helper1 = helper1->pDown;
							}
							counter1 = 1;
								
							deleter = deleter->pNext;
							if (deleter->pNext == nullptr)
							{
								break;

							}

							helper1 = helper1->pNext;
							
						}
						
						delete deleter;
						
						if (counter1 == 0)
						{
							helper1->pDown = nullptr;
						}
						else
						{
							helper1->pNext = nullptr;
						}

						deleter = searcher;
						helper1 = searcher;
						counter1 = 0;
					}
					if (searcher == head)
					{
						head = head->pNext;
						delete searcher;
					}
					else
					{
						Node* helper = head;
						while (helper->pNext != searcher)
						{
							helper = helper->pNext;
						}
						helper->pNext = searcher->pNext;
						delete searcher;
					}
					size_book--;//
					counter = 1;
					stack<string> helper;
					while (!names.empty())
					{
						helper.push(names.top());
						names.pop();
					}
					while (!helper.empty())
					{
						if (counter == index_book)
						{
							helper.pop();
						}
						if (!helper.empty())
						{
							counter++;
							names.push(helper.top());
							helper.pop();
						}
					}
					break;
				}
			}
			return void();
		}
		searcher = searcher->pNext;
		counter++;
	}
	cout << "Ошибка книга не найдена!" << endl;
}

void hierarchy::changer_string(int index_book, int index_string)
{
}

void hierarchy::changer_word(int index_book, int index_string, int index_word)
{
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
		cout << "5. Rewrite book." << endl;
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
			case 5:
				system("cls");
				cout << "Enter index of book" << endl;
				cin >> index_f;
				list.changer_book(index_f);
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


