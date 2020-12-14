#include <iostream>

using namespace std;



class Matrix
{
	long int** arr;
	int line;
	int column;
public:
	Matrix();
	Matrix(int line_column);
	Matrix(int line, int column);
	~Matrix();
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	Matrix operator+(const Matrix& other);
	Matrix& operator+=(const Matrix& other);
	Matrix operator-(const Matrix& other);
	Matrix operator*(const Matrix& other);
	Matrix operator*(const int other);
	bool operator==(const Matrix& other);
	bool operator!=(const Matrix& other);
	friend ostream& operator<< (ostream& stream, const Matrix& other);
	void easy_fill_int();

	
};


Matrix::Matrix()
{
	arr = nullptr;
	this->line = 0;
	this->column = 0;
}


Matrix::Matrix(int line_column)
{
	arr = new long int * [line_column];

	for (int i = 0; i < line_column; i++)
	{
		arr[i] = new long int[line_column];
	}

	this->line = 0;
	this->column = 0;
}


Matrix::Matrix(int line, int column)
{
	this->line = line;
	this->column = column;

	arr = new long int * [line];

	for (int i = 0; i < line; i++)
	{
		arr[i] = new long int[column];
	}
}


Matrix::~Matrix()
{
	if (arr != nullptr)
	{
		for (int i = 0; i < line; i++)
		{
			delete [] arr[i];
		}

		delete [] arr;
	}
}


Matrix::Matrix(const Matrix& other)
{
	this->line = other.line;
	this->column = other.column;
	this->arr = new long int * [line];

	for (int i = 0; i < line; i++)
	{
		this->arr[i] = new long int[column];
	}

	for (int i = 0; i < line; i++) {
		for (int j = 0; j < column; j++) {
			this->arr[i][j] = other.arr[i][j];
		}
	}	
}


Matrix& Matrix::operator=(const Matrix& other)
{
	if (arr == nullptr)
	{
		this->line = other.line;
		this->column = other.column;
		this->arr = new long int * [line];

		for (int i = 0; i < line; i++)
		{
			this->arr[i] = new long int[column];
		}

		for (int i = 0; i < line; i++) {
			for (int j = 0; j < column; j++) {
				this->arr[i][j] = other.arr[i][j];
			}
		}
		return*this;
	}
	else
	{
		for (int i = 0; i < line; i++)
		{
			delete[] arr[i];
		}

		delete[] arr;

		this->line = other.line;
		this->column = other.column;
		this->arr = new long int * [line];

		for (int i = 0; i < line; i++)
		{
			this->arr[i] = new long int[column];
		}

		for (int i = 0; i < line; i++) {
			for (int j = 0; j < column; j++) {
				this->arr[i][j] = other.arr[i][j];
			}
		}
		return*this;
	}
}

Matrix Matrix::operator+(const Matrix& other)
{
	if (line == other.line && column == other.column)
	{
		Matrix temp(line, column);
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				temp.arr[i][j] = this->arr[i][j] + other.arr[i][j];
			}
		}
		return temp;
	}
}

Matrix& Matrix::operator+=(const Matrix& other)
{
	if (line == other.line && column == other.column)
	{
		
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				this->arr[i][j] = this->arr[i][j] + other.arr[i][j];
			}
		}
		return *this;
	}
}

Matrix Matrix::operator-(const Matrix& other)
{
	if (line == other.line && column == other.column)
	{
		Matrix temp(line, column);
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				temp.arr[i][j] = this->arr[i][j] - other.arr[i][j];
			}
		}
		return temp;
	}
}

Matrix Matrix::operator*(const Matrix& other)
{
	
	if (column == other.line)
	{
		Matrix temp(line, other.column);
		
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < other.column; j++)
			{
				temp.arr[i][j] = 0;
			}
		}
		
		for (int j = 0; j < other.column; j++)
		{
			for (int l = 0; l < line; l++)
			{
				for (int k = 0; k < column; k++)
				{
					temp.arr[l][j] = temp.arr[l][j] + this->arr[l][k] * other.arr[k][j];
				}
			}
		}
		
		return temp;
	}
}

Matrix Matrix::operator*(const int other)
{
	Matrix temp(*this);
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < column; j++)
		{
			temp.arr[i][j] = temp.arr[i][j] * other;
		}
	}
	return temp;
}

bool Matrix::operator==(const Matrix& other)
{
	if (line == other.line && column == other.column)
	{
		for (int i = 0; i < line; i++)
		{
			for (int j = 0; j < column; j++)
			{
				if (arr[i][j] != other.arr[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		return false;
	}
}

bool Matrix::operator!=(const Matrix& other)
{
	return !(this->operator==(other));
}




void Matrix::easy_fill_int()
{
	for (int i = 0; i < line; i++)
	{
		for (int j = 0; j < column; j++)
		{
			arr[i][j] = i + j;
		}
	}
}

ostream& operator<<(ostream& stream, const Matrix& other)
{
	for (int i = 0; i < other.line; i++) {
		for (int j = 0; j < other.column; j++) {
			stream << other.arr[i][j] << "\t";
		}
		stream << endl;
	}
	return stream;
}

int main()
{
	Matrix art(3, 3);
	art.easy_fill_int();
	cout << art << endl;
	Matrix lol(3, 4);
	lol.easy_fill_int();
	cout << lol << endl;

	Matrix jo = art * lol;
	
	cout << jo;
	cout << (art != lol);
	return 0;
}


