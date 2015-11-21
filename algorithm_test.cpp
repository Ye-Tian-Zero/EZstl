#include<string>
#include<iostream>
#include"EZ_list.h"
#include"EZ_algorithm.h"
using std::string;
using std::cout;
using std::endl;
int main(){
	list<int> ilst1, ilst2;
	for (int i(1); i <= 9; ++i)
	{
		ilst2.push_back(i);
	}
	for (int i(1); i <= 5; ++i)
	{
		ilst1.push_back(i);
	}

	cout << *(mismatch(ilst1.begin(), ilst1.end(), ilst2.begin()).first) << endl;
	cout << *(mismatch(ilst1.begin(), ilst1.end(), ilst2.begin()).second) << endl;

	cout << equal(ilst1.begin(), ilst1.end(), ilst2.begin()) << endl;
	cout << equal(ilst1.begin(), ilst1.end(), ++ilst2.begin()) << endl;

	fill(ilst1.begin(), ilst1.end(), 9);
	for (auto n : ilst1)
	{
		cout << n << ' ';
	}
	cout << endl;

	fill_n(ilst1.begin(), 3, 7);
	for (auto n : ilst1)
	{
		cout << n << ' ';
	}
	cout << endl;

	auto ite1 = ilst1.begin();
	auto ite2 = ite1;
	advance(ite2, 3);

	iter_swap(ite1, ite2);
	cout << *ite1 << ' ' << *ite2 << endl;
	for (auto n : ilst1)
	{
		cout << n << ' ';
	}
	cout << endl;

	cout << max(*ite1, *ite2) << endl;
	cout << min(*ite1, *ite2) << endl;

	swap(*ilst1.begin(), *ilst2.begin());
	for (auto n : ilst1)
	{
		cout << n << ' ';
	}
	cout << endl;
	for (auto n : ilst2)
	{
		cout << n << ' ';
	}
	cout << endl;

	string stra1[] = { "good", "better", "best" };
	string stra2[] = { "good", "fetter", "fest" };

	cout << ::lexicographical_compare(stra1, stra1 + 2, stra2, stra2 + 2);

	system("pause");
	return 0;
}