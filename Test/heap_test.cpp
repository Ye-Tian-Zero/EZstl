#include"EZ_heap.h"
#include<vector>
#include<iostream>
using std::vector;
using std::cout;
using std::endl;

int main()
{
	int ia[9] = { 0, 1, 2, 3, 4, 8, 9, 3, 5 };
	/*vector<int> ivec(ia, ia + 9);

	make_heap(ivec.begin(), ivec.end());
	for (auto n : ivec)
	{
		cout << n << ' ';
	}
	cout << endl;

	ivec.push_back(7);
	push_heap(ivec.begin(), ivec.end());
	for (auto n : ivec)
	{
		cout << n << ' ';
	}
	cout << endl;

	pop_heap(ivec.begin(), ivec.end());
	cout << ivec.back() << endl;
	ivec.pop_back();
	for (auto n : ivec)
	{
		cout << n << ' ';
	}
	cout << endl;

	sort_heap(ivec.begin(), ivec.end());
	for (auto n : ivec)
	{
		cout << n << ' ';
	}
	cout << endl*/;

	make_heap(ia, ia+9);
	for (auto n : ia)
	{
		cout << n << ' ';
	}
	cout << endl;

	sort_heap(ia, ia + 9);
	for (auto n : ia)
	{
		cout << n << ' ';
	}
	cout << endl;

	system("pause");
	return 0;
}