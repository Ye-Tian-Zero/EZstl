#ifndef EZ_LIST_H
#define EZ_LIST_H
#include"EZ_iterator.h"
#include"EZ_simple_alloc.h"
#include"EZ_construct.h"
#include<cstddef>


template<class T>
struct __listNode{
	typedef __listNode<T>* node_pointer;
	node_pointer next;
	node_pointer prev;
	T data;
};

template<class T, class Ref, class Ptr>
struct __list_iterator{

	typedef __list_iterator<T, T&, T*>		iterator;
	typedef __list_iterator<T, Ref, Ptr>	self;

	typedef bidirectional_iterator_tag		iterator_category;
	typedef T								value_type;
	typedef Ptr								pointer;
	typedef	ptrdiff_t						difference_type;
	typedef Ref								reference;
	typedef size_t							size_type;
	typedef __listNode<T>*					link_type;

	link_type node;

	__list_iterator(link_type x) : node(x){}
	__list_iterator(){}
	__list_iterator(const iterator& x) : node(x.node){}

	bool operator== (const self& x)const { return node == x.node; }
	bool operator!= (const self& x)const { return node != x.node; }

	reference operator* ()const { return node->data; }

	pointer operator->() const{ return &(operator*()); }

	self& operator++(){
		node = node->next;
		return *this;
	}

	self operator++(int){
		self tmp = *this;
		++ *this;
		return tmp;
	}

	self& operator--(){
		node = node->prev;
		return *this;
	}

	self& operator--(int){
		self tmp = *this;
		-- *this;
		return tmp;
	}
};


template<class T, class Alloc = alloc>
class list{
protected:
	typedef __listNode<T>	listNode;
	typedef simple_alloc<listNode, Alloc> list_node_allocator;

public:
	typedef __list_iterator<T, T&, T*> iterator;
	typedef __list_iterator<T, const T&, const T*> const_iterator;
	typedef listNode*		link_type;
	typedef T				value_type;
	typedef T*				pointer;
	typedef T&				reference;
	typedef ptrdiff_t		difference_type;
	typedef size_t			size_type;

protected:

	link_type node;

	link_type get_node(){
		return list_node_allocator::allocate();
	}

	void put_node(link_type p){
		list_node_allocator::deallocate(p);
	}

	link_type create_node(const T& x){
		link_type loc = get_node();
		construct(&(loc->data), x);
		return loc;
	}

	void destory_node(link_type p){
		destory(&(p->data));
		put_node(p);
	}


	void empty_initialize()
	{
		node = get_node();
		node->next = node;
		node->prev = node;
	}

public:

	iterator begin(){ return node->next; }
	iterator end(){ return node; }

	bool empty() const{ return node->next == node; }

	size_type size() const{
		size_type result = 0;
		result = distance(begin(), end());
		return result;
	}

	size_type size(){
		size_type result = 0;
		result = distance(begin(), end());
		return result;
	}

	reference front(){ return *begin(); }
	reference back(){ return *(--end()); }

	list() { empty_initialize(); }
	~list()
	{
		link_type first = begin().node;
		for (; first != node;)
		{
			link_type tmp = first->next;
			destory_node(first);
			first = tmp;
		}

		destory(node);
	}

	void push_back(const T& x){ insert(end(), x); }

	iterator insert(iterator position, const T& x)
	{
		link_type tmp = create_node(x);
		tmp->next = position.node;
		tmp->prev = position.node->prev;
		(position.node)->prev->next = tmp;
		(position.node)->prev = tmp;
		return tmp;
	}

	void push_front(const T& x)
	{
		insert(begin(), x);
	}

	iterator erase(iterator position)
	{
		link_type next_node = position.node->next;
		next_node->prev = position.node->prev;
		position.node->prev->next = next_node;
		destory_node(position.node);
		return next_node;
	}

	void pop_front(){ erase(begin()); }
	void pop_back(){ erase(--end()); }

	void clear()
	{
		link_type cur = begin().node;
		while (cur != node)
		{
			link_type tmp = cur;
			cur = cur->next;
			destory_node(tmp);
		}

		node->next = node;
		node->prev = node;
	}

	void remove(const T& value)
	{
		iterator first = begin();
		iterator last = end();
		while (first != last)
		{
			if (*first == value)
			{
				first = erase(first);
			}
			else
				++first;
		}
	}

	void unique()
	{
		iterator first = begin();
		iterator last = end();
		if (first == last)
			return;
		iterator next = first;
		while (++next != last)
		{
			if (*next == *first)
			{
				 erase(next);
			}
			else
			{
				first = next;
			}
			next = first;
		}
	}

private:
	void transfer(iterator position, iterator first, iterator last)
	{
		if (position != last)
		{
			last.node->prev->next = position.node;
			first.node->prev->next = last.node;
			position.node->prev->next = first.node;
			link_type tmp = first.node->prev;
			first.node->prev = position.node->prev;
			position.node->prev = last.node->prev;
			last.node->prev = tmp;
		}
	}

public:
	void splice(iterator position, list& x)
	{
		if (!x.empty())
		{
			transfer(position, x.begin(), x.end());
		}
	}

	void splice(iterator position, list&, iterator i)
	{
		iterator j = i;
		++j;
		if (position == i || position == j)
			return;
		transfer(position, i, j);
	}

	void splice(iterator position, list&, iterator first, iterator last)
	{
		if (first != last)
			transfer(position, first, last);
	}

	void merge(list<T, Alloc>& x)
	{
		iterator first1 = begin();
		iterator first2 = x.begin();
		iterator last1 = end();
		iterator last2 = x.end();

		while (first1 != last1 && first2 != last2)
		{
			if (*first2 < *first1)
			{
				iterator next = first2;
				transfer(first1, first2, ++next);
				first2 = next;
			}
			else
				++first1;
		}

		if (first2 != last2)
			transfer(last1, first2, last2);
	}

	void reverse()
	{
		iterator first = begin();
		++first;
		while (first != end())
		{
			iterator tmp = first;
			++first;
			transfer(begin(), tmp, first);
		}
	}

	void swap(list& x)
	{
		link_type tmp = x.node;
		x.node = this->node;
		this->node = tmp;
	}

	void sort()
	{
		if (node->next == node || node->next->next == node)
			return;

		list<T, Alloc> carry;
		list<T, Alloc> counter[64];

		int fill(0);

		while (!empty())
		{
			carry.splice(carry.begin(), *this, begin());
			int i(0);
			while (i != fill && !counter[i].empty())
			{
				counter[i].merge(carry);
				carry.swap(counter[i++]);
			}
			carry.swap(counter[i]);
			if (i == fill) ++fill;
		}

		for (int i = 1; i < fill; ++i)
			counter[i].merge(counter[i - 1]);
		swap(counter[fill - 1]);
	}

};
#endif