#ifndef EZ_PAIR_H
#define EZ_PAIR_H
template<class T1, class T2>
struct pair{
	pair(){}
	pair(T1 f, T2 s) :first(f), second(s){}
	T1 first;
	T2 second;
};
#endif