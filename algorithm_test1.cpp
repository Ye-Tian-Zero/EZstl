#include<iostream>
#include<string>
#include"EZ_algorithm.h"
#include"EZ_vector.h"
#include"EZ_deque.h"
#include"EZ_list.h"
#include<fstream>
std::wfstream a;

using std::cout;
using std::endl;
using std::string;

template<class T>
struct display{
	void operator()(const T& x) const
	{
		cout << x << ' ';
	}
};

struct even{
	bool operator()(int x) const
	{
		return x % 2 ? false : true;
	}
};

class even_by_two{
public:
	int operator()()const
	{
		return _x += 2;
	}
private:
	static int _x;
};

int even_by_two::_x = 0;

int main()
{
	vector<int> ivec;
	ivec.push_back(0);
	ivec.push_back(1);
	ivec.push_back(2);
	ivec.push_back(3);
	ivec.push_back(4);
	ivec.push_back(5);
	ivec.push_back(6);
	ivec.push_back(6);
	ivec.push_back(6);
	ivec.push_back(7);
	ivec.push_back(8);
	vector<int> ivec2(2,6);

	cout << *adjacent_find(ivec.begin(), ivec.end()) << endl;

	cout << count(ivec.begin(), ivec.end(), 6) << endl;

	cout << *find(ivec.begin(), ivec.end(), 4) << endl;
	
	cout << *(find_first_of(ivec.begin(), ivec.end(), ivec2.begin(), ivec2.end()) + 3) << endl;

	for_each(ivec.begin(), ivec.end(), display<int>());
	cout << endl;

	generate(ivec2.begin(), ivec2.end(), even_by_two());
	for_each(ivec2.begin(), ivec2.end(), display<int>());
	cout << endl;

	generate(ivec.begin(), ivec.begin() + 3, even_by_two());
	for_each(ivec.begin(), ivec.end(), display<int>());
	cout << endl;

	remove(ivec.begin(), ivec.end(), 6);
	for_each(ivec.begin(), ivec.end(), display<int>());
	cout << endl;

	vector<int> ivec3(12);
	remove_copy(ivec.begin(), ivec.end(), ivec3.begin(), 6);
	for_each(ivec3.begin(), ivec3.end(), display<int>());
	cout << endl;

	replace(ivec.begin(), ivec.end(), 6, 3);
	for_each(ivec.begin(), ivec.end(), display<int>());
	cout << endl;

	reverse(ivec.begin(), ivec.end());
	for_each(ivec.begin(), ivec.end(), display<int>());
	cout << endl;

	rotate(ivec.begin(), ivec.begin() + 4, ivec.end());
	for_each(ivec.begin(), ivec.end(), display<int>());
	cout << endl;

	cout << *max_element(ivec.begin(), ivec.end()) << endl;
	cout << *min_element(ivec.begin(), ivec.end()) << endl;

	partition(ivec.begin(), ivec.end(), even());
	for_each(ivec.begin(), ivec.end(), display<int>());
	cout << endl;

	unique(ivec.begin(), ivec.end());
	for_each(ivec.begin(), ivec.end(), display<int>());
	cout << endl;

	system("pause");
	return 0;

}