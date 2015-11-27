#include"EZ_vector.h"
#include"EZ_numeric.h"
#include<iostream>
#include<iterator>

using std::cout;
using std::endl;
int main()
{
	vector<int> ivec;
	for (int i(1); i != 6; ++i)
	{
		ivec.push_back(i);
	}

	cout << accumulate(ivec.begin(), ivec.end(), 0) << endl;
	cout << inner_product(ivec.begin(), ivec.end(), ivec.begin(), 10) << endl;
	std::ostream_iterator<int> oite(cout, " ");
	partial_sum(ivec.begin(), ivec.end(), oite);
	cout << endl;
	adjacent_difference(ivec.begin(), ivec.end(), oite);

	system("pause");
	return 0;
}