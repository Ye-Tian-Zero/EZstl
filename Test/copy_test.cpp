#define test
#include"EZ_deque.h"
#include"EZ_algorithm.h"
#include"EZ_list.h"
#include"EZ_vector.h"
#include<string>
#include<iostream>
using std::cout;
using std::endl;

class C{
public:
	C() : _data(3){}
private:
	int _data;
};

int main(){
	const char ccs[5] = { 'a', 'b', 'c', 'd', 'e' };
	char ccd[5];
	copy(ccs, ccs + 5, ccd);
	cout << endl;
	const wchar_t cwcs[5] = { 'a', 'b', 'c', 'd', 'e' };
	wchar_t cwcd[5];
	copy(cwcs, cwcs + 5, cwcd);
	cout << endl;

	int ia[5] = { 1, 2, 3, 4, 5 };
	copy(ia, ia + 5, ia);
	cout << endl;

	list<int> ilst;
	ilst.push_back(1);
	ilst.push_back(1);
	ilst.push_back(1);
	ilst.push_back(1);
	copy(ilst.begin(), ilst.end(), ilst.begin());
	cout << endl;

	vector<int> ivecs(5,1);
	copy(ivecs.begin(), ivecs.end(), ivecs.begin());
	cout << endl;

	vector<C> Cvs(5);
	copy(Cvs.begin(), Cvs.end(), Cvs.begin());
	cout << endl;

	deque<C> Cds(5,C());
	copy(Cds.begin(), Cds.end(), Cds.begin());
	cout << endl;

	vector<std::string> strvs(5, "good");
	::copy(strvs.begin(), strvs.end(), strvs.begin());
	cout << endl;

	system("pause");
	return 0;
}