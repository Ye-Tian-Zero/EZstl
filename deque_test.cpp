#include"EZ_deque.h"
#include<iostream>
using std::cout;
using std::endl;
int main()
{
	deque<int> ideq;
	ideq.push_back(1);
	ideq.push_back(1);
	ideq.push_back(2);
	ideq.push_back(2);
	ideq.push_back(2);
	ideq.push_back(2);
	ideq.push_back(2);
	ideq.push_back(2);
	ideq.push_back(2);
	ideq.push_back(2);
	ideq.push_back(2);
	ideq.push_back(2);
	ideq.push_back(2);
	ideq.push_back(2);
	ideq.push_back(3);
	ideq.push_back(3);
	ideq.push_back(3);
	ideq.push_back(3);
	ideq.push_back(3);
	ideq.push_back(3);
	ideq.push_back(3);
	for (auto n : ideq)
	{
		cout << n << endl;
	}
	system("pause");
}