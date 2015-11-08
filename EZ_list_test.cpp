#include"EZ_list.h"
#include"EZ_vector.h"
#include<vector>
#include<iostream>
#include<algorithm>
using std::cout;
using std::endl;

class list_test{
	list_test(const list_test&){ cout << "copy constructor" << endl; }
	~list_test(){ cout << "destructor" << endl; }
};

int main()
{
	list<int> ilst;

	for (int i(0); i != 6; ++i)
	{
		ilst.push_back(i);
	}

	auto iter = ilst.begin();
	for (int i(0); i != 4; ++i)
		++iter;

	ilst.insert(iter, 999);

	for (auto n : ilst)
	{
		cout << n << " "; 
	}

	cout << endl;
	cout << endl;

	for (int i(0); i != 9; ++i)
	{
		ilst.push_back(i);
	}

	for (auto n : ilst)
	{
		cout << n << " "; 
	}

	cout << endl;
	cout << endl;

	ilst.erase(ilst.begin());
	for (auto n : ilst)
	{
		cout << n << " "; 
	}

	cout << endl;
	cout << endl;

	cout << "size" << ilst.size() << endl << endl;
	
	ilst.remove(1);
	for (auto n : ilst)
	{
		cout << n << " "; 
	}

	cout << endl;
	cout << endl;

	ilst.clear();

	cout << ilst.size() << endl << endl;

	for (int i = 0; i <= 100; ++i)
	{
		ilst.push_back(i / 30);
	}

	for (auto n : ilst)
	{
		cout << n << " "; 
	}

	cout << endl;
	cout << endl;

	ilst.unique();
	for (auto n : ilst)
	{
		cout << n << " "; 
	}

	cout << endl;
	cout << endl;
	
	list<int> ilst2;
	for (int i(0); i != 9; ++i)
	{
		ilst2.push_back(i);
	}

	ilst2.transfer(ilst.begin(), ilst.end(), ilst2.begin());

	for (auto n : ilst2)
	{
		cout << n << " "; 
	}


	cout << endl;
	cout << "size of ilst: " << ilst.size() << endl;
	cout << endl;

	system("pause");
	return 0;
}