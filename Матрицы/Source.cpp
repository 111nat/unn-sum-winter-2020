#include <iostream>

using namespace std;

template<typename T>
class Vector
{
	T* vector;
	int Size;
public:
	Vector(int size = 3)
	{
		Size = size;
		vector = new T[Size];
		for (int i = 0; i < Size; i++)
		{
			vector[i] = 0;
		}
	}
	~Vector()
	{
		delete[] vector;
	}
	int GetSize()
	{
		return Size;
	}
	Vector(const Vector& other)
	{
		Size = other.Size;
		vector = new T[Size];
		for (int i = 0; i < Size; i++)
		{
			vector[i] = other.vector[i];
		}
	}
	bool operator==(const Vector& other)
	{
		if (Size = other.Size)
		{
			for (int i = 0; i < Size; i++)
			{
				if (vector[i] != other.vector[i])
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	Vector& operator=(const Vector& other)
	{
		if (this != &other)
		{
			delete[] vector;
			Size = other.Size;
			vector = new T[Size];
			for (int i = 0; i < Size; i++)
			{
				vector[i] = other.vector[i];
			}
		}
		return *this;
	}
	Vector operator+(const T& other)
	{
		Vector temp(Size);
		for (int i = 0; i < Size; i++)
		{
			temp.vector[i] = other = vector[i];
		}
		return temp;
	}
	Vector operator-(const T& other)
	{
		Vector temp(Size);
		for (int i = 0; i < Size; i++)
		{
			temp.vector[i] = vector[i] - other;
		}
		return temp;
	}
	Vector operator*(const T& other)
	{
		Vector temp(Size);
		for (int i = 0; i < Size; i++)
		{
			temp.vector[i] = vector[i] * other;
		}
		return temp;
	}
	Vector operator+(const Vector& other)
	{
		if (Size == other.Size)
		{
			Vector temp(Size);
			for (int i = 0; i < Size; i++)
			{
				temp.vector[i] = vector[i] + other.vector[i];
			}
			return temp;
		}
		else
		{
			cout << "size != other.size" << endl;
			return Vector();
		}
	}
	Vector operator-(const Vector& other)
	{
		if (Size == other.Size)
		{
			Vector temp(Size);
			for (int i = 0; i < Size; i++)
			{
				temp.vector[i] = vector[i] - other.vector[i];
			}
			return temp;
		}
		else
		{
			cout << "size != other.size" << endl;
			return Vector();
		}
	}
	Vector operator*(const Vector& other)
	{
		if (Size == other.Size)
		{
			Vector temp(Size);
			for (int i = 0; i < Size; i++)
			{
				temp.vector[i] = vector[i] * other.vector[i];
			}
			return temp;
		}
		else
		{
			cout << "size != other.size" << endl;
			return Vector();
		}
	}
	friend istream& operator>>(istream& stream, const Vector& other)
	{
		for (int i = 0; i < other.Size; i++)
		{
			stream >> other.vector[i];
		}
		return stream;
	}
	friend ostream& operator<<(ostream& stream, const Vector& other)
	{
		for (int i = 0; i < other.Size; i++)
		{
			stream << other.vector[i] << " ";
		}
		stream << endl;
		return stream;
	}
	T& GetValue(int index)
	{
		if (index < Size && index > -1)
		{
			return vector[index];
		}
		else
		{
			cout << "size != other.size" << endl;
			return T();
		}
	}
	T& operator[](int index)
	{
		if (index < Size && index > -1)
		{
			return vector[index];
		}
		else
		{
			cout << "size != other.size" << endl;
			//return T();
		}
	}
};


template<typename T>
class Matrix
{
	T** arr;
	int line;
	int column;
public:
	Matrix()
	{
		arr = nullptr;
		this->line = 0;
		this->column = 0;
	}
	Matrix(int line_column)
	{
		arr = new T* [line_column];
		
		for (int i = 0; i < line_column; i++)
		{
			arr[i] = new T[line_column];
		}
		
		this->line = line_column;
		this->column = line_column;
	}
	Matrix(int line, int column)
	{
		this->line = line;
		this->column = column;
		
		arr = new T * [line];
		
		for (int i = 0; i < line; i++)
		{
			arr[i] = new T[column];
		}
	}
	~Matrix()
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
	Matrix(const Matrix& other)
	{
		this->line = other.line;
		this->column = other.column;
		this->arr = new T * [line];
		
		for (int i = 0; i < line; i++)
		{
			this->arr[i] = new T[column];
		}
		
		for (int i = 0; i < line; i++) {
			for (int j = 0; j < column; j++) {
				this->arr[i][j] = other.arr[i][j];
			}
		}	
	}
	Matrix& operator=(const Matrix& other)
	{
		if (arr == nullptr)
		{
			this->line = other.line;
			this->column = other.column;
			this->arr = new T * [line];
			
			for (int i = 0; i < line; i++)
			{
				this->arr[i] = new T[column];
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
			this->arr = new T * [line];
			
			for (int i = 0; i < line; i++)
			{
				this->arr[i] = new T[column];
			}
			
			for (int i = 0; i < line; i++) {
				for (int j = 0; j < column; j++) {
					this->arr[i][j] = other.arr[i][j];
				}
			}
			return*this;
		}
	}
	Matrix operator+(const Matrix& other)
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
	Matrix& operator+=(const Matrix& other)
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
	Matrix operator-(const Matrix& other)
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
	Matrix operator*(const Matrix& other)
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
	Matrix operator*(const int other)
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
	bool operator==(const Matrix& other)
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
	bool operator!=(const Matrix& other)
	{
		return !(this->operator==(other));
	}
	friend ostream& operator<< (ostream& stream, const Matrix& other)
	{
		for (int i = 0; i < other.line; i++) {
			for (int j = 0; j < other.column; j++) {
				stream << other.arr[i][j] << "\t";
			}
			stream << endl;
		}
		return stream;
	}
	friend istream& operator>>(istream& stream,  Matrix& other)
	{
		if (other.arr != nullptr)
		{


			for (int i = 0; i < other.line; i++) {
				for (int j = 0; j < other.column; j++) {
					stream >> other.arr[i][j];
				}
			}
			return stream;
		}
		else
		{
			Vector<T> vec;

			other.arr = new T * [vec.GetSize()];

			for (int i = 0; i < vec.GetSize(); i++)
			{
				other.arr[i] = new T[vec.GetSize()];
			}

			other.line = vec.GetSize();
			other.column = vec.GetSize();

			for (int i = 0; i < vec.GetSize(); i++)
			{
				cin >> vec;
				for (int j = 0; j < vec.GetSize(); j++)
				{
					other.arr[i][j] = vec[j];
				}
			}
		}
	}

	
};


int main()
{
	

	Matrix<int> a;
	cin >> a;
	cout << a;
	/*Matrix<int> art(3, 3);
	cin >> art;
	cout << art << endl;
	Matrix<int> lol(3, 4);
	cin >> lol;
	cout << lol << endl;

	Matrix<int> jo = art * lol;
	
	cout << jo;
	cout << (art != lol);*/
	
	return 0;
}


