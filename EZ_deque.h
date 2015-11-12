#ifndef EZ_DEQUE_H
#define EZ_DEQUE_H
#include "EZ_iterator.h"
#include "EZ_simple_alloc.h"

template<class T, class Ref, class Ptr, size_t BufSiz>
struct __deque_iterator{

	typedef __deque_iterator<T, T&, T*, BufSiz>					iterator;
	typedef __deque_iterator<T, const T&, const T*, BufSiz>		const_iterator;

	static size_t buffer_size()	{ return __deque_buf_size(BufSiz, sizeof(T)); }

	typedef random_access_iterator_tag	iterator_category;
	typedef T							value_type;
	typedef Ptr							pointer;
	typedef Ref							reference;
	typedef size_t						size_type;
	typedef ptrdiff_t					difference_type;
	typedef T**							map_pointer;

	typedef __deque_iterator			self;

	T* cur;
	T* first;
	T* last;
	map_pointer node;

	static inline size_t __deque_buf_size(size_t n, size_t sz)
	{
		return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
	}

	void set_node(map_pointer new_node)
	{
		node = new_node;
		first = *new_node;
		last = first + difference_type(buffer_size());
	}

	reference operator*() const { return *cur; }

	pointer operator->() const { return &(operator*()) };

	difference_type operator-(const self& x) const{
		return difference_type(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
	}

	self& operator++(){
		++cur;
		if (cur == last){
			set_node(node + 1);
			cur = first;
		}
		return *this;
	}

	self operator++(int){
		self tmp = *this;
		++*this;
		return tmp;
	}

	self& operator--(){
		if (cur == first)
		{
			set_node(node - 1);
			cur = last;
		}
		--cur;
		return *this;
	}

	self operator--(int){
		self tmp = *this;
		--*this;
		return tmp;
	}

	self& operator+=(difference_type n)
	{
		difference_type offset = n + cur - first;

		if (offset > 0 && offset < difference_type(buffer_size()))
		{
			cur += n;
		}
		else
		{
			difference_type node_offset = offset > 0 ? offset / difference_type(buffer_size())
													 : -difference_type((-offset - 1) / buffer_size()) - 1;

			set_node(node + node_offset);
			
			cur = first + (offset - node_offset * difference_type(buffer_size()));
		}

		return *this;
	}

	self operator+(difference_type n) const{
		self tmp = *this;
		return tmp += n;
	}

	self& operator-=(difference_type n) const{ return *this += -n; }

	self operator-(difference_type n) const{
		self tmp;
		return tmp -= n;
	}

	reference operator[](difference_type n){ return *(*this + n) }

	bool operator ==(const self& x){
		return cur == x.cur;
	}
	
	bool operator !=(const self& x){
		return !(*this == x);
	}

	bool operator <(const self& x){
		return node == x.node ? (cur < x.cur) : (node < x.node);
	}
};

template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque{
public:
	typedef T			value_type;
	typedef T*			pointer;
	typedef T&			reference;
	typedef ptrdiff_t	difference_type;
	typedef size_t		size_type;

	typedef __deque_iterator<T, T&, T*, BufSiz> iterator;
	typedef simple_alloc<value_type, alloc> data_allocator;
	typedef simple_alloc<pointer, alloc> map_allocator;

protected:

	static size_type initial_map_size(){ return 8; }

	typedef pointer*	map_pointer;

	iterator start;
	iterator finish;

	map_pointer map;

	size_type map_size;

public:

	deque() :start(), finish(), map(0), map_size(0){
		create_map_and_nodes(0);
	}

	iterator begin(){ return start; }
	iterator end(){ return finish; }

	reference operator[](size_type n){
		return start[difference_type(n)];
	}

	reference front(){
		return *start;
	}

	reference back(){
		iterator tmp = finish;
		--tmp;
		return *tmp;
	}

	size_type size() const{ return finsh - start; }

	size_type max_size() const{ return size_type(-1); }

	bool empty() const{ return finish == start; }

	deque(int n, const value_type& value)
		:start(), finish(), map(0), map_size(0)
	{
		fill_initialize(n, value);
	}

	difference_type buffer_size()
	{
		return start.buffer_size();
	}

	void fill_initialize(size_type n, const value_type& value)
	{
		create_map_and_nodes(n);
		map_pointer cur;
		for (cur = start.node; cur < finish.node; ++cur)
		{
			uninitialized_fill(*cur, *cur + buffer_size(), value);
		}
		
		uninitialized_fill(finish.first, finish.cur, value);
	}

	void create_map_and_nodes(size_type num_elements)
	{
		size_type num_nodes = num_elements / buffer_size() + 1;

		map_size = max(initial_map_size(), num_nodes + 2);

		map = map_allocator::allocate(map_size);

		map_pointer nstart = map + (map_size - num_nodes) / 2;
		map_pointer nfinish = nstart + num_nodes - 1;

		map_pointer cur;

		for (cur = nstart; cur <= nfinish; ++cur)
		{
			*cur = allocate_node();
		}

		start.set_node(nstart);
		finish.set_node(nfinish);

		start.cur = start.first;
		finish.cur = finish.first + num_elements % buffer_size();
	}

protected:
	pointer allocate_node(){ return data_allocator::allocate(buffer_size()); }

	void deallocate_node(pointer p){ data_allocator::deallocate(p, buffer_size()); }

	void push_back_aux(const value_type& t){
		value_type t_copy = t;
		reserve_map_at_back();
		*(finish.node + 1) = allocate_node();
		construct(finish.cur, t_copy);
		finish.set_node(finish.node + 1);
		finish.cur = finish.first;
	}

	void push_front_aux(const value_type& t){
		value_type t_copy = t;
		reserve_map_at_front();
		*(start.node - 1) = allocate_node();
		start.set_node(start.node + 1);
		start.cur = start.last - 1;
		construct(start.cur, t_copy);
	}

	void reserve_map_at_back(size_type nodes_to_add = 1){
		if (nodes_to_add + 1 > map_size - (finish.node - map))
			reallocate_map(nodes_to_add, false);
	}

	void reserve_map_at_front(size_type nodes_to_add = 1){
		if (start.node - map < nodes_to_add)
			reallocate_map(nodes_to_add, true);
	}

	void reallocate_map(size_type nodes_to_add, bool add_at_front){
		size_type old_num_nodes = finish.node - start.node + 1;
		size_type new_num_nodes = old_num_nodes + nodes_to_add;

		map_pointer new_nstart;

		if (map_size > 2 * new_num_nodes){
			new_nstart = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
			if (new_nstart < start.node)
				copy_tmp(start.node, finish.node + 1, new_nstart);
			else
				copy_backward_tmp(start.node, finish.node + 1, new_nstart + old_num_nodes);
		}
		else{
			size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;
			map_pointer new_map = map_allocator::allocate(new_map_size);
			new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);

			copy_tmp(start.node, finish.node + 1, new_nstart);
			map_allocator::deallocate(map, map_size);

			map = new_map;
			map_size = new_map_size;
		}

		start.set_node(new_nstart);
		finish.set_node(new_nstart + old_num_nodes - 1);
	}

public:
	void push_back(const value_type& t){
		if (finish.cur != finish.last - 1){
			construct(finish.cur, t);
			++(finish.cur);
		}
		else
			push_back_aux(t);
	}

	void push_front(const value_type& t){
		if (start.cur != start.first)
		{
			construct(start.cur - 1, t);
			--(start.cur);
		}
		else
			push_front_aux(t);
	}
private:
	template<class T>
	T max(T v1, T v2)
	{
		return v1 >= v2 ? v1 : v2;
	}
	
	template<class ForwardIterator>
	inline ForwardIterator copy_tmp(ForwardIterator first, ForwardIterator last, ForwardIterator result)
	{
		for (; first != last; ++first, ++result)
		{
			*result = *first;
		}
		return result;
	}

	template<class ForwardIterator>
	inline void copy_backward_tmp(ForwardIterator src_end, ForwardIterator src_start, ForwardIterator dst)
	{
		while (--src_start >= src_end)
		{
			*(--dst) = *src_start;
		}
	}
};

#endif