#pragma once
#include<iostream>
#include<vector>
using namespace std;

template<typename T>
struct ThirdArray
{
	size_t _x;
	size_t _y;
	T _value;
	ThirdArray(const size_t& row, const size_t& col, const T& value)
		:_x(row)
		, _y(col)
		, _value(value)
	{}
};

template<typename T>
class SpareMatric
{
	typedef ThirdArray<T> ThirdArray;
public:
	SpareMatric(T* array,const size_t& row,const size_t& col,const T& invalid)
		:_row(row)
		, _col(col)
		, _invalid(invalid)
	{
		for (size_t i = 0; i < row; i++)
		{
			for (size_t j = 0; j < col; j++)
			{
				if (array[i*col + j] != invalid)
				{
					_array.push_back(ThirdArray(i, j, array[i*col + j]));
				}
			}
		}
	}

	void Display()
	{
		size_t index = 0;
		for (size_t i = 0; i < _row; i++)
		{
			for (size_t j = 0; j < _col; j++)
			{
				if (index < _array.size() && _array[index]._x==i&&_array[index]._y==j)
				{
					cout << _array[index]._value << " ";
					index++;
				}
				else
				{
					cout << _invalid<< " ";
				}
			}
			cout << endl;
		}

	}

	void print()
	{
		size_t index = 0;
		while (index < _array.size())
		{
			cout << _array[index]._value << " ";
			index++;
		}
	}

protected:
	vector<ThirdArray> _array;
	size_t _row;
	size_t _col;
	T _invalid;
};