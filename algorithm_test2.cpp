#include"EZ_algorithm.h"
#include"EZ_vector.h"
#include<iostream>
using std::cout;
using std::endl;
#define display(x) for(auto n:x){cout << n << ' ';}cout<<endl;

struct even{
	bool operator()(int x) const{ return x % 2 ? false : true; }
};

int main()
{
	int ia[] = { 12, 17, 20, 22, 23, 30, 33, 40 };
	vector<int> iv;
	for (auto val : ia)
	{
		iv.push_back(val);
	}
	cout << *lower_bound(iv.begin(), iv.end(), 21) << endl;
	cout << *upper_bound(iv.begin(), iv.end(), 21) << endl;
	cout << *lower_bound(iv.begin(), iv.end(), 22) << endl;
	cout << *upper_bound(iv.begin(), iv.end(), 22) << endl;
	
	cout << binary_search(iv.begin(), iv.end(), 33) << endl;
	cout << binary_search(iv.begin(), iv.end(), 34) << endl;
	
	display(iv);
	next_permutation(iv.begin(), iv.end());
	display(iv);
	prev_permutation(iv.begin(), iv.end());
	display(iv);

	iv.clear();
	for (int i(17); i != 0; -- i)
	{
		iv.push_back(i);
	}
	display(iv);

	partial_sort(iv.begin(), iv.begin() + 4, iv.end());
	display(iv);

	//__insertion_sort(iv.begin(), iv.end());
	sort(iv.begin(), iv.end());
	display(iv);

	
	system("pause");
}
