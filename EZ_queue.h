#ifndef EZ_QUEUE_H
#define EZ_QUEUE_H
#include"EZ_deque.h"
#include"EZ_vector.h"
#include"EZ_heap.h"

template<class T, class Sequence = deque<T>>
class queue{
	template<class T, class Sequence>
	friend bool operator==(const queue<T, Sequence>&x, const queue<T, Sequence>& y);

public:
	typedef typename Sequence::value_type		value_type;
	typedef typename Sequence::size_type		size_type;
	typedef typename Sequence::reference		reference;
	typedef typename Sequence::const_reference	const_reference;

protected:
	Sequence c;
public:
	bool empty(){ return c.empty(); }
	size_type size(){ return c.size(); }
	reference front(){ return c.front(); }
	const_reference front() const { return c.front(); }
	reference back(){ return c.back(); }
	const_reference back() const { return c.back(); }
	void push(const value_type& x) { c.push_back(x); }
	void pop() { c.pop_front(); }
};

template<class T, class Sequence>
bool operator==(const queue<T, Sequence>& x, const queue<T, Sequence>& y)
{
	return x.c == y.c;
}

template<class T, class Sequence = vector<T>>
class priority_queue{
public:
	typedef typename Sequence::value_type		value_type;
	typedef typename Sequence::size_type		size_type;
	typedef typename Sequence::reference		reference;
	typedef typename Sequence::const_reference	const_reference;

protected:
	Sequence c;

public:
	priority_queue() : c(){}
	bool empty(){ return c.empty(); }
	size_type size(){ return c.size(); }
	const_reference top() const{ return c.front(); }
	void push(const value_type& x){
		c.push_back(x);
		push_heap(c.begin(), c.end());
	}

	void pop()
	{
		pop_heap(c.begin(), c.end());
		c.pop_back();
	}


};
#endif