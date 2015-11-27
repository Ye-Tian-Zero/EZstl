//#define DEBUG
#include"EZ_stack.h"
#include"EZ_list.h"
#include"EZ_vector.h"
#include <iostream>
#include<string>
using std::string;
using std::cin;
using std::cout;
using std::endl;
int main()
{
	vector<int> ivec(10,10);
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