//#define DEBUG
#include"EZ_vector.h"
#include<vector>
#include <iostream>
using std::cout;
using std::endl;
int main()
{
	vector<int> ivec;
	for (int i = 0; i != 10; ++i)
	{
		ivec.push_back(i);
	}
	for (auto iter = ivec.begin(); iter != ivec.end(); ++ iter)
	{
		std::cout << *iter << ", ";
	}
	cout << endl;
	cout << "size: " << ivec.size() << endl;
	cout << "capacity: " << ivec.capacity() << endl;
	ivec.erase(ivec.begin(), ivec.end());
	cout << "size: " << ivec.size() << endl;
	cout << "capacity: " << ivec.capacity() << endl;
	ivec.resize(1000, 20);
	cout << "size: " << ivec.size() << endl;
	cout << "capacity: " << ivec.capacity() << endl;
	ivec.resize(10);
	cout << "size: " << ivec.size() << endl;
	cout << "capacity: " << ivec.capacity() << endl;
	for (auto n : ivec)
	{
		cout << n << ", ";
	}
	cout << endl;
	system("pause");
	return 0;
}