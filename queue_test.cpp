#include"EZ_queue.h"
#include"EZ_list.h"
#include<iostream>

using std::cout;
using std::endl; 

int main()
{
	queue<int> iq;

	for (int i = 0; i != 100; ++i)
		iq.push(i);

	while (iq.size())
	{
		cout << iq.front() << " ";
		iq.pop();
	}
	cout << endl;

	queue<int, list<int>> ilq;

	for (int i = 0; i != 100; ++i)
		ilq.push(i);

	while (ilq.size())
	{
		cout << ilq.front() << " ";
		ilq.pop();
	}
	cout << endl;

	system("pause");
	return 0;
}