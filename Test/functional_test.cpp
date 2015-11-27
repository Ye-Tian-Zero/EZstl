#include"EZ_functional.h"
#include"EZ_algorithm.h"
#include"EZ_vector.h"
#include<iostream>
using std::cout;
using std::endl;
int main()
{
	vector<int> ivec;
	for (int i(0); i != 10; ++i)
	{
		ivec.push_back(i);
	}
	
	cout << *find_if(ivec.begin(), ivec.end(), bind2nd(greater<int>(), 3)) << endl;
	system("pause");
	return 0;
}