#include"EZalloc.h"
#include <iostream>
#include <vector>
int main()
{
	int ia[5] = { 1, 2, 3, 4, 5 };
	std::vector<int, EZ::allocator<int>> iv(ia, ia + 5);
	for (int i(0); i != iv.size(); ++i)
	{
		std::cout << iv[i] << ' ';
	}
	std::cout << std::endl;
	return 0;
}