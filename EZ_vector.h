#ifndef EZ_VECTOR_H
#define EZ_VECTOR_H

#include"EZ_simple_alloc.h"
#include"EZ_construct.h"
#include"EZ_iterator.h"

#include<cstddef>

template<class ForwardIterator, class T>
void vec_fill(ForwardIterator first, ForwardIterator last, T value)
{
	for (; first != last; ++first)
	{
		*first = value;
	}
}

template<class T, class Alloc = alloc>
class vector{

public:
	typedef T			value_type;
	typedef T*			pointer;
	typedef T&			reference;
	typedef T*			iterator;
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;
	typedef const T*	const_pointer;
	typedef const T&	const_reference;

protected:
	typedef simple_alloc<value_type, alloc> data_allocator;

	iterator start;
	iterator finish;
	iterator end_of_storage;

	void insert_aux(iterator position, const T& x);
	void insert(iterator position, size_type n, const T& x);

	void deallocate()
	{
		if (start)
			data_allocator::deallocate(start, end_of_storage - start);
	}

	void fill_initialize(size_type n, const T& value)
	{
		start = allocate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	}

public:

	iterator begin(){ return start; }
	iterator end(){ return finish; }

	size_type size() const { return size_type(finish - start); }
	size_type capacity() const { return size_type(end_of_storage - start); }
	bool empty() const{ return begin() == end(); }
	reference operator[](size_type n){ return *(start + n); }

	vector() :start(0), finish(0), end_of_storage(0){}
	vector(size_type n, const T& value) { fill_initialize(n, value); }
	vector(int n, const T& value){ fill_initialize(n, value); }
	vector(long n, const T& value){ fill_initialize(n, value); }
	explicit vector(size_type n){ fill_initialize(n, T()); }

	~vector()
	{
		destory(start, finish);
		deallocate();//析构当然释放空间了。。。。。。, 然clear却不。
	}

	reference front(){ return *start; }
	reference back(){ return *(finish - 1); }

	void push_back(const T& v)
	{
		if (finish != end_of_storage)
		{
			construct(finish, v);
			++finish;
		}
		else
			insert_aux(end(), v);
	}

	void pop_back()
	{
		--finish;
		destory(finish);
	}

	iterator erase(iterator position)
	{
		if (position + 1 != end())
		{
			//copy(position + 1, finish, position);//Don't know
			uninitialized_copy(position + 1, finish, position);
		}
		--finish;
		destory(finish);
		return position;
	}

	iterator erase(iterator first, iterator last)
	{
		//copy? why?
		uninitialized_copy(last, finish, first);
		size_t n = last - first;
		destory(finish - n, finish);
		finish -= n;
		return first;
	}

	void resize(size_type new_sz, const T& x)
	{
		if (new_sz < size())
			erase(begin() + new_sz, finish);
		else
			insert(end(), new_sz- size(), x);
	}
	
	void resize(size_type new_sz)
	{
		resize(new_sz, T());
	}

	void clear()
	{
		erase(begin(), end()); //no memory released
	}

protected:
	iterator allocate_and_fill(size_type n, const T& x)
	{
		iterator result = data_allocator::allocate(n);
		uninitialized_fill_n(result, n, x);
		return result;
	}
};

template<class T, class Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T& x)
{
	if (finish != end_of_storage)
	{
		construct(finish, *(finish - 1));
		++finish;
		T x_copy = x;
//		copy_backward(position, finish - 2, finish - 1);
		iterator src_start = finish - 2;
		iterator dst_start = finish - 1;
		iterator src_end = position;

		while (--src_start >= src_end)
		{
			*(--dst_start) = *src_start;
		}
		*position = x_copy;
	}
	else
	{
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2 * old_size : 1;
		iterator new_start = data_allocator::allocate(len);
		iterator new_finish = new_start;

		try{
			new_finish = uninitialized_copy(start, position, new_start);
			construct(new_finish, x);

			++new_finish;
			new_finish = uninitialized_copy(position, finish, new_finish);
		}
		catch (...)
		{
			destory(new_start, new_finish);
			data_allocator::deallocate(new_start, len);
			throw;
		}

		destory(start, finish);
		deallocate();
		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}
}

template<class T, class Alloc>
void vector<T, Alloc>::insert(iterator position, size_type n, const T& x)
{
	if (n != 0)
	{
		if (size_type(end_of_storage - finish) >= n)
		{
			T x_copy = x;

			const size_type elems_after = finish - position;

			iterator old_finish = finish;
			if (elems_after > n)
			{
				uninitialized_copy(finish - n, finish, finish);

				finish += n;

				//--------------copy_backward
				iterator src_start = old_finish - n;
				iterator dst_start = old_finish;
				iterator src_end = position;

				while (--src_start >= src_end)
				{
					*(--dst_start) = *src_start;
				}
				//-------------end
				
				vec_fill(position, old_finish, x_copy);
			}

		}
		else
		{
			const size_type old_size = size();
			const size_type new_size = old_size + (old_size > n ? old_size : n);

			iterator new_start = data_allocator::allocate(new_size);
			iterator new_finish = new_start;
				
			try{
				new_finish = uninitialized_copy(start, position, new_start);

				new_finish = uninitialized_fill_n(new_finish, n, x);

				new_finish = uninitialized_copy(position, finish, new_finish);
			}
			catch(...)
			{
				destory(new_start, new_finish);
				data_allocator::deallocate(new_start, new_size);
			}

			destory(start, finish);
			deallocate();

			start = new_start;
			finish = new_finish;
			end_of_storage = start + new_size;
		}
	}
}

#endif