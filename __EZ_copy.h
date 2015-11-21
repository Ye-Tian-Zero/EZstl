#ifndef __EZ_COPY_H
#define __EZ_COPY_H
#ifdef test
#include<iostream>
using std::cout;
using std::endl;
#endif
#include<cstring>
#include"EZ_iterator.h"
#include"EZ_type_traits.h"

template<class T>
inline T* __copy_t(const T* first, const T* last, T* result, __false_type)
{
#ifdef test
	cout << "__copy_t without trivial assignment operator" << endl;
#endif
	return __copy_d(first, last, result, (ptrdiff_t*) 0);
}

template<class T>
inline T* __copy_t(const T* first, const T* last, T* result, __true_type)
{
#ifdef test
	cout << "__copy_t with trivial assignment operator" << endl;
#endif
	std::memmove(result, first, sizeof(T) * (last - first));
	return result + (last - first);
}


template<class RandomAccessIterator, class OutputIterator, class Distance>
inline OutputIterator
__copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*)
{
#ifdef test
	cout << "__copy_d " << endl;
#endif
	for (Distance n = last - first; n > 0; --n, ++result, ++first)
		*result = *first;
	return result;
}

template<class InputIterator, class OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag)
{
#ifdef test
	cout << "__copy input_iterator_tag" << endl;
#endif
	for (; first != last; ++first, ++result)
		 *result = *first;
	return first;
}

template<class RandomAccessIterator, class OutputIterator>
inline OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, random_access_iterator_tag)
{
#ifdef test
	cout << "__copy random_iterator_tag" << endl;
#endif
	return __copy_d(first, last, result, distance_type(first));
}

inline char* copy(const char* first, const char* last, char* result)
{
#ifdef test
	cout << "char* copy" << endl;
#endif
	std::memmove(result, first, last - first);
	return result + (last - first);
}

inline wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result)
{
#ifdef test
	cout << "wchar_t* copy" << endl;
#endif
	std::memmove(result, first, sizeof(wchar_t) * (last - first));//byte-wise copy, so ...
	return result + (last - first);
}

template<class InputIterator, class OutputIterator>
struct __copy_dispatch{
	OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result){
		#ifdef test
			cout << "__copy_dispatch general" << endl;
		#endif
		return __copy(first, last, result, iterator_category(first));
	}
};

template<class T>
struct __copy_dispatch < T*, T* > {
	T* operator()(T* first, T* last, T* result){
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		#ifdef test
			cout << "__copy_dispatch T* T*" << endl;
		#endif
		return __copy_t(first, last, result, t());
	}
};

template<class T>
struct __copy_dispatch <const T*, T* > {
	T* operator()(T* first, T* last, T* result){
		typedef typename __type_traits<T>::has_trivial_assignment_operator t;
		#ifdef test
			cout << "__copy_dispatch const T* T*" << endl;
		#endif
		return __copy_t(first, last, result, t());
	}
};


#endif