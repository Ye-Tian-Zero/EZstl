#ifndef EZ_ALGORITHM_H
#define EZ_ALGORITHM_H

#include"EZ_iterator.h"
#include"EZ_pair_structure.h"
#include"__EZ_copy.h"
#include<cstring>

template <class InputIterator1, class InputIterator2>
inline bool equal(InputIterator1 first1, InputIterator2 last1, InputIterator2 first2)
{
	for (; first1 != last1; ++first1, ++first2)
		if (*first1 != *first2)
			return false;
	return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
inline bool equal(InputIterator1 first1, InputIterator2 last1, InputIterator2 first2, BinaryPredicate binary_pred)
{
	for (; first1 != last1; ++first1, ++first2)
		if (!binary_pred(*first1, *first2))
			return false;
	return true;
}

template<class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value)
{
	for (; first != last; ++first)
		*first = value;
}

template<class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value)
{
	for (; n > 0; --n, ++first)
		*first = value;
	return first;
}

template<class ForwardIterator1, class ForwardIterator2>
inline void iter_swap(ForwardIterator1 iter1, ForwardIterator2 iter2)
{
	typename iterator_traits<ForwardIterator1>::value_type value(*iter1);
	*iter1 = *iter2;
	*iter2 = value;
}

template<class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2)
{
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
	{
		if (*first1 < *first2)
			return true;
		if (*first1 > * first2)
			return false;
	}
	return first1 == last1  && first2 != last2;
}

template<class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
	InputIterator2 first2, InputIterator2 last2, Compare comp)
{
	for (; first1 != last1 && first2 != last2; ++first1, ++first2)
	{
		if (comp(*first1, *first2))
			return true;
		if (comp(*first2, *first1))
			return false;
	}
	return first1 == last1  && first2 != last2;
}

inline bool
lexicographical_compare(const unsigned char* first1,
						const unsigned char* last1,
						const unsigned char* first2,
						const unsigned char* last2)
{
	const size_t len1 = last1 - first1;
	const size_t len2 = last2 - first2;
	const size_t to_cmp = len1 > len2 ? len2 : len1;
	const int result = std::memcmp(first1, first2, to_cmp);
	return result != 0 ? result < 0 : len1 < len2;
}

template<class T>
inline const T& max(const T& a, const T& b){
	return a < b ? b : a;
}

template<class T, class Compare>
inline const T& max(const T& a, const T& b, Compare comp){
	return comp(a, b) ? b : a;
}

template<class T>
inline const T& min(const T& a, const T& b){
	return b < a ? b : a;
}

template<class T, class Compare>
inline const T& min(const T& a, const T& b, Compare comp){
	return comp(b, a) ? b : a;
}

template<class InputIterator1, class InputIterator2>
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
	for (; first1 != last1; ++first1, ++first2)
	{
		if (*first1 != *first2)
			return pair<InputIterator1, InputIterator2>(first1, first2);
	}
	return pair<InputIterator1, InputIterator2>(first1, first2);
}

template<class InputIterator1, class InputIterator2, class BinaryPredicate>
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_pred){
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!binary_pred(*first1, *first2))
			return pair<InputIterator1, InputIterator2>(first1, first2);
	}
	return pair<InputIterator1, InputIterator2>(first1, first2);
}

template<class T>
inline void swap(T& a, T& b)
{
	T tmp = a;
	a = b;
	b = tmp;
}

template<class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result){
	return __copy_dispatch<InputIterator, OutputIterator>() (first, last, result);
}

#endif