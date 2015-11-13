#ifndef EZ_CONSTRUCT_H
#define EZ_CONSTRUCT_H
#include<new>
#include"EZ_type_traits.h"
#include"EZ_iterator.h"

template<class T1, class T2>
inline void construct(T1* p, T2& value)
{
	new(p) T1(value);
}

template<class T>
inline void destory(T* ptr)
{
	ptr->~T();
}

template<class ForwardIterator>
inline void destory(ForwardIterator first, ForwardIterator last)
{
	__destory(first, last, value_type(first));
}

template<class ForwardIterator, class T>
inline void __destory(ForwardIterator first, ForwardIterator last, T*)
{
	typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
	__destory_aux(first, last, trivial_destructor());
}

template<class ForwardIterator>
inline void
__destory_aux(ForwardIterator first, ForwardIterator last, __false_type)
{
	for (; first < last; ++first)
		destory(&(*first));
}

template<class ForwardIterator>
inline void __destory_aux(ForwardIterator first, ForwardIterator second, __true_type){
#ifdef DEBUG
	std::cout << "trivial_destructor" << std::endl;
#endif
}

inline void destory(char*, char*){}
inline void destory(wchar_t*, wchar_t*){}

template<class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __true_type)
{
	while (n--)
	{
		*first = x;
		++first;
	}
	return first;
}

template<class ForwardIterator, class Size, class T>
inline ForwardIterator __uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, __false_type)
{
	while (n--)
	{
		construct(&(*fisrt), x);
		first++;
	}
	return first;
}

template<class ForwardIterator, class Size, class T, class T1>
inline ForwardIterator __uninitialized_fill_n(ForwardIterator first, Size n, const T& x, T1)
{
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	return __uninitialized_fill_n_aux(first, n, x, is_POD());
}

template<class ForwardIterator, class Size, class T>
inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x)
{
	return __uninitialized_fill_n(first, n, x, value_type(first));
}

template<class ForwardIterator>
ForwardIterator
__uninitialized_copy_aux(ForwardIterator first, ForwardIterator last, ForwardIterator result, __true_type)
{
	ForwardIterator cur = result;
	for (; first != last; ++first, ++cur)
	{
		*cur = *first;
	}
	
	return cur;
}

template<class ForwardIterator>
ForwardIterator
__uninitialized_copy_aux(ForwardIterator first, ForwardIterator last, ForwardIterator result, __false_type)
{
	ForwardIterator cur = result;
	for (; first != last; ++first, ++cur)
	{
		construct(&(*cur), *first);
	}
	return cur;
}

template<class ForwardIterator, class T>
ForwardIterator
__uninitialized_copy(ForwardIterator first, ForwardIterator last, ForwardIterator result, T)
{
	typedef typename __type_traits<T>::is_POD_type is_POD;
	return	__uninitialized_copy_aux(first, last, result, is_POD());
}

template<class ForwardIterator>
ForwardIterator
uninitialized_copy(ForwardIterator first, ForwardIterator last, ForwardIterator result)
{
	return __uninitialized_copy(first, last, result, value_type(result));
}

template<class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& val, __true_type)
{
	for (ForwardIterator cur = first; cur != last; ++cur)
	{
		*cur = val;
	}
}

template<class ForwardIterator, class T>
inline void __uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& val, __false_type)
{
	for (ForwardIterator cur = first; cur != last; ++cur)
	{
		construct(&*cur, val);
	}
}

template<class ForwardIterator, class T, class T1>
inline void __uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& val, T1)
{
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	__uninitialized_fill_aux(first, last, val, is_POD());
}


template<class ForwardIterator, class T>
inline void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& val)
{
	__uninitialized_fill(first, last, val, value_type(first));
}
#endif