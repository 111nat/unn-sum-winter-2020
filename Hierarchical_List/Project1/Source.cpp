#include <iostream>
#include <fstream>//для работы с файлами
#include <stack>
#include <string>
using namespace std;

//хранилище имен .txt
stack<string> names;

//открытие файла для чтения. Закидывает все в path
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

//Открывает файл для перезаписи
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

//Открывает файл для дописи
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

//Иерархический класс
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
	hierarchy();//конструктор
	void push_back(string data);//закидывание .txt файлов
	string print_book(int book);//печатает всю книгу
	string print_string(int book, int string);//печатает строку
	string print_word(int book, int stringg, int word);//печатает слово

	//возвращает кол-во книг
	int get_size_books()
	{
		return size_book;
	}

	//возвращает кол-во строк в определенной книге
	int get_size_string(int index_book)
	{
		Node* curent = head;
		int counter = 1;

		while (curent != nullptr)
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
					return new_counter;
				}
				else
				{
					cout << "Строка не найдена" << endl;
					return int();
				}
			}
			curent = curent->pNext;
			counter++;
		}
		cout << "Error" << endl;
		return int();
	}

	//возвращает кол-во слов в определенной книге и сторке
	int get_size_word(int index_book, int index_string)
	{
		Node* curent = head;
		int counter_b = 1;
		int counter_s = 1;

		while (curent != nullptr)
		{
			if (counter_b == index_book)
			{
				if (curent->pDown != nullptr)
				{
					curent = curent->pDown;

					while (curent != nullptr)
					{
						if (counter_s == index_string)
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

								return new_counter;
							}
							else
							{
								cout << "Слово не найдено." << endl;
								return int();
							}
						}
						curent = curent->pNext;
						counter_s++;
					}
				}
				else
				{
					cout << "Строка не найдена" << endl;
					return int();
				}
			}
			counter_b++;
			curent = curent->pNext;
		}
		cout << "Error" << endl;
		return int();
	}

	//изменяет книгу
	void changer_book(int index_book);

	//изменяет строчку
	void changer_string(int index_book, int index_string);

	//изменяет слово
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
		size_string = 0;

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

		//поиск книги
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

			//поиск книги
			while (current != nullptr)
			{
				if (counter_b == book)
				{
					current = current->pDown;

					//поиск строки
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
			cout << "Ошибка! Книга не найдена" << endl;
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

		//поиск книги
		while (current != nullptr)
		{
			if (counter_b == book)
			{
				current = current->pDown;

				//поиск строки
				while (current != nullptr)
				{
					if (counter_s == stringg)
					{
						//подсчет кол-ва слов в строчке
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

						//поиск слова
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

	//поиск книги
	while (searcher != nullptr)
	{
		if (counter == index_book)
		{
			string new_book = string();
			cout << "Enter new book." << endl;

			//выкидывает все из cin
			while ((char)cin.get() != '\n')
			{
			}

			//для записи с пробелами
			getline(cin, new_book);
			open_file_rewrite(new_book, index_book);
			int choose = 0;

			while (1) {
				//добвка текста 
				cout << "Хотите продолжить на новой строке" << endl;
				cout << "1 or 0" << endl;
				cin >> choose;

				if (choose == 1)
				{
					cout << "Enter continuation." << endl;
					new_book = string();

					while ((char)cin.get() != '\n')
					{
					}

					getline(cin, new_book);
					open_file_add(new_book, index_book);
				}
				else
				{
					//удаление всего связанного с книгой, которую изменили
					Node* deleter = searcher;
					Node* helper1 = searcher;
					int counter1 = 0;

					//само удаление нодов
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

					//удаление книги
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

					size_book--;
					counter = 1;

					//удаление имени файла из хранилища
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
	if (index_book <= get_size_books() && index_string <= get_size_string(index_book))
	{
		int counter = 1;
		Node* searcher = head;
		Node* first_string = head;
		Node* book = head;

		//поиск книги
		while (searcher != nullptr)
		{
			if (counter == index_book)
			{
				break;
			}

			book = book->pNext;
			searcher = searcher->pNext;
			first_string = first_string->pNext;
			counter++;
		}

		if (searcher->pDown != nullptr)
		{
			first_string = first_string->pDown;
			searcher = searcher->pDown;
			int counter_s = 1;

			//новая строка
			string new_str = string();
			cout << "Enter new string." << endl;

			while ((char)cin.get() != '\n')
			{
			}

			getline(cin, new_str);

			//поиск строки
			while (searcher != nullptr)
			{
				if (counter_s == index_string)
				{
					searcher->data = new_str;
					break;
				}

				counter_s++;
				searcher = searcher->pNext;
			}

			//переписка всего файла
			open_file_rewrite(first_string->data, index_book);

			while (first_string->pNext != nullptr)
			{
				first_string = first_string->pNext;
				open_file_add(first_string->data, index_book);
			}

			//удаление
			Node* deleter = book;
			Node* helper1 = book;
			int counter1 = 0;

			while (1)
			{
				if (book->pDown == nullptr)
				{
					break;
				}
				//в самый низ
				while (deleter->pDown != nullptr)
				{
					deleter = deleter->pDown;

					if (deleter->pDown != nullptr)
					{
						helper1 = helper1->pDown;
					}
				}

				//максимум права если есть
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

				deleter = book;
				helper1 = book;
				counter1 = 0;
			}

			//удаление книги
			if (book == head)
			{
				head = head->pNext;
				delete book;
			}
			else
			{
				Node* helper = head;
				while (helper->pNext != book)
				{
					helper = helper->pNext;
				}
				helper->pNext = book->pNext;
				delete book;
			}

			size_book--;
			counter = 1;

			//удаление название файла .txt
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
		}
		else
		{
			cout << "Строк меньше: " << get_size_string(counter) << endl;
			return void();
		}
	}
	else
	{
		cout << "Книг меньше: " << get_size_books() << endl;
		cout << "Или строк: " << get_size_string(index_book) << endl;
		return void();
	}
}

void hierarchy::changer_word(int index_book, int index_string, int index_word)
{
	if (index_book <= get_size_books() && index_string <= get_size_string(index_book) && index_word <= get_size_word(index_book, index_string))
	{
		int counter_b = 1;
		int counter_s = 1;
		int counter_w = 1;
		Node* searcher = head;
		Node* this_string = head;
		Node* first_word = head;
		Node* first_string = head;
		Node* book = head;

		//поиск книги
		while (searcher != nullptr)
		{
			if (counter_b == index_book)
			{
				searcher = searcher->pDown;
				this_string = this_string->pDown;
				first_word = first_word->pDown;
				first_string = first_string->pDown;

				//поиск строки
				while (searcher != nullptr)
				{
					if (counter_s == index_string)
					{
						first_word = first_word->pDown;
						searcher = searcher->pDown;

						//поиск слова
						while (searcher != nullptr)
						{
							if (counter_w == index_word)
							{
								cout << "Enter new word." << endl;
								string new_str = string();
								cin >> new_str;
								searcher->data = new_str;
								this_string->data = string();
								
								//закидка в строку
								while (first_word != nullptr)
								{
									int i = 0;

									while (first_word->data[i] != '\0')
									{
										this_string->data.push_back(first_word->data[i]);
										i++;
										
									}

									this_string->data.push_back(' ');
									
									first_word = first_word->pNext;
								}
								
								//повтор кода
								first_string->data.pop_back();
								open_file_rewrite(first_string->data, index_book);

								while (first_string->pNext != nullptr)
								{
									first_string = first_string->pNext;
									first_string->data.pop_back();
									open_file_add(first_string->data, index_book);
								}

								Node* deleter = book;
								Node* helper1 = book;
								int counter1 = 0;
								while (1)
								{
									if (book->pDown == nullptr)
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

									deleter = book;
									helper1 = book;
									counter1 = 0;
								}

								if (book == head)
								{
									head = head->pNext;
									delete book;
								}
								else
								{
									Node* helper = head;
									while (helper->pNext != book)
									{
										helper = helper->pNext;
									}
									helper->pNext = book->pNext;
									delete book;
								}
								size_book--;
								int counter = 1;
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
								return void();
							}
							searcher = searcher->pNext;
							counter_w++;
						}
					}
					counter_s++;
					searcher = searcher->pNext;
					this_string = this_string->pNext;
					first_word = first_word->pNext;
				}
			}
			counter_b++;
			searcher = searcher->pNext;
			this_string = this_string->pNext;
			first_word = first_word->pNext;
			first_string = first_string->pNext;
			book = book->pNext;
		}
	}
	else
	{
		cout << "Кол-во книг: " << get_size_books() << endl;
		cout << "Кол-во строк: " << get_size_string(index_book) << endl;
		cout << "Кол-во слов: " << get_size_word(index_book, index_string) << endl;
		return void();
	}
}

//объявление объекта
hierarchy list;

//добавка книг .txt
void plus_books()
{
	string PATH = string();
	cout << "Введите книгу .txt" << endl;
	cin >> PATH;
	PATH = PATH + ".txt";
	
	stack<string> helper;

	while (!names.empty())
	{
		if (names.top() == PATH)
		{
			cout << "Такая книга уже есть." << endl;
			return void();
		}
		helper.push(names.top());
		names.pop();
	}

	while (!helper.empty())
	{
		names.push(helper.top());
		helper.pop();
	}
	
	list.push_back(open_file(PATH));
	
}

//интерфейс
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
		cout << "6. Rewrite string." << endl;
		cout << "7. Rewrite word." << endl;
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

			case 6:
				system("cls");
				cout << "Enter index of book and string" << endl;
				cin >> index_f;
				cin >> index_s;
				list.changer_string(index_f, index_s);
				break;

			case 7:
				system("cls");
				cout << "Enter index of book and string and word" << endl;
				cin >> index_f;
				cin >> index_s;
				cin >> index_t;
				list.changer_word(index_f, index_s, index_t);
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