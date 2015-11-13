#include"EZ_stack.h"
#include<string>
#include<iostream>
using std::string;
using std::cin;
using std::cout;
using std::endl;
int main()
{
	stack<int> istk;
	bool leagal = true;
	string s;
	cin >> s;
	for (auto n : s)
	{
		if (n == '(')
		{
			istk.push(n);
		}
		else if (n == ')')
		{
			if (istk.empty() || istk.top() != '(')
			{
				leagal = false;
				break;
			}
			istk.pop();
		}
	}

	if (!istk.empty() || !leagal)
	{
		cout << "error" << endl; 
	}

	else
	{
		cout << "right" << endl;
	}
	system("pause");
	return 0;
}