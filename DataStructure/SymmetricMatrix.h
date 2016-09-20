#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<typename T>
class SymmetricMatrix
{
public:
	SymmetricMatrix(T* array, size_t row)
		:_row(row)
	{
		for (size_t i = 0; i< row; i++)
		{
			for (size_t j = 0; j <= i;j++)
			{
				_array.push_back(array[i*row+j]);
			}
		}
	}
	void Display()
	{
		for (size_t i = 0; i < _row; i++)
		{
			for (size_t j = 0; j <_row; j++)
			{
				cout << Access(i, j)<<" ";
			}
			cout << endl;
		}
	}
private:
	T Access(size_t i, size_t j)
	{
		if (j>i)
		{
			swap(i, j);
		}
		return _array[i*(i + 1) / 2 + j];
	}

protected:
	vector<T> _array;
	size_t _row;
};