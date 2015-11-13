#ifndef EZ_STACK_H
#define EZ_STACK_H
#include"EZ_deque.h"


template<class T, class Sequence = deque<T>>
class stack{
	template <class T, class Sequence>
	friend bool operator==(const stack<T, Sequence>& x, const stack<T, Sequence>& y);
public:
	typedef typename Sequence::value_type		value_type;
	typedef typename Sequence::size_type		size_type;
	typedef typename Sequence::reference		reference;
	//typedef typename Sequence::const_reference	value_type;
protected:
	Sequence c;
public:
	bool empty() const{ return c.empty(); }

	size_type size() { return c.size(); }

	reference top() { return c.back(); }

	void push(const value_type& val) { c.push_back(val); }

	void pop() { c.pop_back(); }
};

template <class T, class Sequence>
bool operator==(const stack<T, Sequence>& x, const stack<T, Sequence>& y)
{
	return x.c == y.c;
}

#endif