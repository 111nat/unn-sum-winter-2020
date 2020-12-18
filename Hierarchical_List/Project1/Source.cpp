#include <iostream>
#include <fstream>//��� ������ � �������
#include <stack>
#include <string>
using namespace std;

//��������� ���� .txt
stack<string> names;

//�������� ����� ��� ������. ���������� ��� � path
string open_file(string path)
{
	ifstream harry_1;
	harry_1.open(path);
	string book = string();
	
	if (!harry_1.is_open())
	{
		cout << "������ �������� �����!" << endl;
	}
	else
	{
		cout << "���� ������!" << endl;
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

//��������� ���� ��� ����������
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
		cout << "������ �������� �����!" << endl;
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

//��������� ���� ��� ������
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
		cout << "������ �������� �����!" << endl;
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

//������������� �����
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
	hierarchy();//�����������
	void push_back(string data);//����������� .txt ������
	string print_book(int book);//�������� ��� �����
	string print_string(int book, int string);//�������� ������
	string print_word(int book, int stringg, int word);//�������� �����

	//���������� ���-�� ����
	int get_size_books()
	{
		return size_book;
	}

	//���������� ���-�� ����� � ������������ �����
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
					cout << "������ �� �������" << endl;
					return int();
				}
			}
			curent = curent->pNext;
			counter++;
		}
		cout << "Error" << endl;
		return int();
	}

	//���������� ���-�� ���� � ������������ ����� � ������
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
								cout << "����� �� �������." << endl;
								return int();
							}
						}
						curent = curent->pNext;
						counter_s++;
					}
				}
				else
				{
					cout << "������ �� �������" << endl;
					return int();
				}
			}
			counter_b++;
			curent = curent->pNext;
		}
		cout << "Error" << endl;
		return int();
	}

	//�������� �����
	void changer_book(int index_book);

	//�������� �������
	void changer_string(int index_book, int index_string);

	//�������� �����
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
		//�����
		head = new Node(data);

		//������
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

		//�����
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
		//�����
		Node* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}

		current->pNext = new Node(data);

		//������
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

		//�����
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
		cout << "������! ���� ������." << endl;
		cout << "����� ����: " << size_book << endl;
	}
	else
	{
		int counter = 1;
		Node* current = this->head;

		//����� �����
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
		cout << "������! ����� �� �������" << endl;
	}
	return string();
}

string hierarchy::print_string(int book, int stringg)
{
	if (book > size_book)
	{
		cout << "������! ���� ������." << endl;
		cout << "����� ����: " << size_book << endl;
	}
	else
	{
		if (stringg > size_string)
		{
			cout << "������! ����� ������." << endl;
			cout << "����� �����: " << size_string << endl;
		}
		else
		{
			int counter_b = 1;
			int counter_s = 1;
			Node* current = this->head;

			//����� �����
			while (current != nullptr)
			{
				if (counter_b == book)
				{
					current = current->pDown;

					//����� ������
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

					cout << "������! ������ �� �������" << endl;
					return string();
				}

				current = current->pNext;
				counter_b++;
			}
			cout << "������! ����� �� �������" << endl;
		}
	}
	return string();
}

string hierarchy::print_word(int book, int stringg, int word)
{
	if (book > size_book)
	{
		cout << "������! ���� ������." << endl;
		cout << "����� ����: " << size_book << endl;
	}
	else
	{
		int counter_b = 1;
		int counter_s = 1;
		int counter_w = 1;
		Node* current = this->head;

		//����� �����
		while (current != nullptr)
		{
			if (counter_b == book)
			{
				current = current->pDown;

				//����� ������
				while (current != nullptr)
				{
					if (counter_s == stringg)
					{
						//������� ���-�� ���� � �������
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

						//����� �����
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

						cout << "������! ����� �� �������" << endl;
						cout << "����� ����: " << amount_of_words << endl;
						return string();
					}
					current = current->pNext;
					counter_s++;
				}
				cout << "������! ������ �� �������" << endl;
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

	//����� �����
	while (searcher != nullptr)
	{
		if (counter == index_book)
		{
			string new_book = string();
			cout << "Enter new book." << endl;

			//���������� ��� �� cin
			while ((char)cin.get() != '\n')
			{
			}

			//��� ������ � ���������
			getline(cin, new_book);
			open_file_rewrite(new_book, index_book);
			int choose = 0;

			while (1) {
				//������ ������ 
				cout << "������ ���������� �� ����� ������" << endl;
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
					//�������� ����� ���������� � ������, ������� ��������
					Node* deleter = searcher;
					Node* helper1 = searcher;
					int counter1 = 0;

					//���� �������� �����
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

					//�������� �����
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

					//�������� ����� ����� �� ���������
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
	cout << "������ ����� �� �������!" << endl;
}

void hierarchy::changer_string(int index_book, int index_string)
{
	if (index_book <= get_size_books() && index_string <= get_size_string(index_book))
	{
		int counter = 1;
		Node* searcher = head;
		Node* first_string = head;
		Node* book = head;

		//����� �����
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

			//����� ������
			string new_str = string();
			cout << "Enter new string." << endl;

			while ((char)cin.get() != '\n')
			{
			}

			getline(cin, new_str);

			//����� ������
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

			//��������� ����� �����
			open_file_rewrite(first_string->data, index_book);

			while (first_string->pNext != nullptr)
			{
				first_string = first_string->pNext;
				open_file_add(first_string->data, index_book);
			}

			//��������
			Node* deleter = book;
			Node* helper1 = book;
			int counter1 = 0;

			while (1)
			{
				if (book->pDown == nullptr)
				{
					break;
				}
				//� ����� ���
				while (deleter->pDown != nullptr)
				{
					deleter = deleter->pDown;

					if (deleter->pDown != nullptr)
					{
						helper1 = helper1->pDown;
					}
				}

				//�������� ����� ���� ����
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

			//�������� �����
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

			//�������� �������� ����� .txt
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
			cout << "����� ������: " << get_size_string(counter) << endl;
			return void();
		}
	}
	else
	{
		cout << "���� ������: " << get_size_books() << endl;
		cout << "��� �����: " << get_size_string(index_book) << endl;
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

		//����� �����
		while (searcher != nullptr)
		{
			if (counter_b == index_book)
			{
				searcher = searcher->pDown;
				this_string = this_string->pDown;
				first_word = first_word->pDown;
				first_string = first_string->pDown;

				//����� ������
				while (searcher != nullptr)
				{
					if (counter_s == index_string)
					{
						first_word = first_word->pDown;
						searcher = searcher->pDown;

						//����� �����
						while (searcher != nullptr)
						{
							if (counter_w == index_word)
							{
								cout << "Enter new word." << endl;
								string new_str = string();
								cin >> new_str;
								searcher->data = new_str;
								this_string->data = string();
								
								//������� � ������
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
								
								//������ ����
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
		cout << "���-�� ����: " << get_size_books() << endl;
		cout << "���-�� �����: " << get_size_string(index_book) << endl;
		cout << "���-�� ����: " << get_size_word(index_book, index_string) << endl;
		return void();
	}
}

//���������� �������
hierarchy list;

//������� ���� .txt
void plus_books()
{
	string PATH = string();
	cout << "������� ����� .txt" << endl;
	cin >> PATH;
	PATH = PATH + ".txt";
	
	stack<string> helper;

	while (!names.empty())
	{
		if (names.top() == PATH)
		{
			cout << "����� ����� ��� ����." << endl;
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

//���������
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