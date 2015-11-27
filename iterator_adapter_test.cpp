#include"EZ_vector.h"
#include"EZ_iterator.h"
#include"EZ_algorithm.h"	
#include"EZ_list.h"
#include<iostream>

using std::cout;
using std::endl;

int main()
{
	vector<int> ivec;
	back_insert_iterator<vector<int>> bi = back_insert(ivec);
	for (int i(0); i != 10; ++i)
	{
		bi = i;
	}

	for (auto n : ivec)
	{
		cout << n << ' ';
	}

	cout << endl;

	list<int> ilst;
	front_insert_iterator<list<int>> fi = front_insert(ilst);
	for (int i(0); i != 10; ++i)
	{
		fi = i;
	}

	for (auto n : ilst)
	{
		cout << n << ' ';
	}
	cout << endl;

	auto liter = ilst.begin();
	for (int i(0); i != 5; ++i)
	{
		++liter;
	}

	auto ii = inserter(ilst, liter);
	for (int i(0); i != 8; ++i)
	{
		ii = i;
	}

	for (auto n : ilst)
	{
		cout << n << ' ';
	}
	cout << endl;

	ivec.clear();
	ivec.resize(ilst.size());
	copy(ilst.begin(), ilst.end(), ivec.rbegin());
	for (auto n : ivec)
	{
		cout << n << ' ';
	}
	cout << endl;

	system("pause");
	return 0;
}