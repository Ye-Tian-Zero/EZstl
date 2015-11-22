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

template<class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last){
	if (first == last) return last;
	ForwardIterator next = first;
	while (++next != last)
	{
		if (*next == *first)
			return first;
		first = next;
	}
	return last;
}

template<class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate binary_pred){
	if (first == last) return last;
	ForwardIterator next = first;
	while (++next != last)
	{
		if (binary_pred(next, first))
			return first;
		first = next;
	}
	return last;
}

template<class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& value)
{
	typename iterator_traits<InputIterator>::difference_type cnt = 0;
	for (; first != last; ++first)
	{
		if (*first == value)
			++cnt;
	}
	return cnt;
}

template<class InputIterator, class Predicate>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, Predicate pred)
{
	typename iterator_traits<InputIterator>::difference_type cnt = 0;
	for (; first != last; ++first)
	{
		if (pred(*first))
			++cnt;
	}
	return cnt;
}

template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value)
{
	while (first != last && *first != value) ++first;
	return first;
}


template<class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred)
{
	while (first != last && !pred(*first)) ++first;
	return first;
}

template<class InputIterator, class ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2)
{
	for (; first1 != last1; ++first1)
		for (ForwardIterator iter = first2; iter != last2; ++iter)
			if (*first1 == *iter)
				return first1;
	return last1;
}

template<class InputIterator, class ForwardIterator, class BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2, BinaryPredicate comp)
{
	for (; first1 != last1; ++first1)
		for (ForwardIterator iter = first2; iter != last2; ++iter)
			if (comp(*first1, *iter))
				return first1;
	return last1;
}

template<class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator, Function f){
	for (; first != last; ++first)
		f(*first);
	return f;
}

template<class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen){
	for (; first != last; ++first)
		*first = gen()
}

template<class OutputIterator, class Size , class Generator>
OutputIterator generate(OutputIterator first, OutputIterator last, Size sz, Generator gen){
	for (; sz > 0; --sz, ++first;)
		*first = gen();
	return first;
}

template<class InputIterator1, class InputIterator2>
bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2){
	while (first1 != last1 && first2 != last2)
	{
		if (*first2 < *first1)
			return false;
		else if (*first1 < *first2)
			++first1;
		else
		{
			++first1; ++first2;
		}
	}
	return first2 == last2;
}

template<class InputIterator1, class InputIterator2, class Compare>
bool includes(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp){
	while (first1 != last1 && first2 != last2)
	{
		if (comp(first2 < first1))
			return false;
		else if (comp(first1 < first2))
			++first1;
		else
		{
			++first1; ++first2;
		}
	}
	return first2 == last2;
}

template<class ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last){
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first != last)
		if (*result < *first)	result = first;
	return result;
}

template<class ForwardIterator, class Compare>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp){
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first != last)
		if (comp(*result, *first)) result = first;
	return result;
}

template<class ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last){
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first != last)
		if (*first < *result)	result = first;
	return result;
}

template<class ForwardIterator, class Compare>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp){
	if (first == last) return first;
	ForwardIterator result = first;
	while (++first != last)
		if (comp(*first, *result)) result = first;
	return result;
}

template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result)
{
	while (first1 != last1 && first2 != last2){
		if (*first2 < *first1){
			*result = *first2;
			++first2;
		}
		else{
			*result = *first1;
			++first1;
		}
		++result;
	}
	return copy(first2, last2, copy(first1, last1, result));//It's sooooo smart!
}


template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp)
{
	while (first1 != last1 && first2 != last2){
		if (comp(*first2, *first1)){
			*result = *first2;
			++first2;
		}
		else{
			*result = *first1;
			++first1;
		}
		++result;
		return copy(first2, last2, copy(first1, last1, result));//It's sooooo smart!
	}
}

template<class BidirectionalIterator, class Predicate>
BidirectionalIterator partition(BidirectionalIterator first, BidirectionalIterator last, Predicate pred){
	while (true){
		while (true)
		{
			if (first == last)
				return first;
			else if (pred(*first))
				++first;
			else break;
		}
		--last;
		while (true)
		{
			if (first == last)
				return first;
			else if (!pred(*first))
				--last;
			else break;
		}
		iter_swap(first, last);
		++first;
	}
}

template<class InputIterator, class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value){
	for (; first != last; ++first)
	{
		if (*first != value){
			*result = *first;
			++result;
		}
	}
	return result;
}

template<class InputIterator, class OutputIterator, class Predicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred){
	for (; first != last; ++first)
	{
		if (!pred(*first)){
			*result = *first;
			++result;
		}
	}
	return result;
}

template<class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value)
{
	first = find(first, last, value);
	ForwardIterator next = first;
	return first == last ? first : remove_copy(++next, last, first, value);
}

template<class ForwardIterator, class Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred)
{
	first = find_if(first, last, perd);
	ForwardIterator next = first;
	return first == last ? first : remove_copy_if(++next, last, first, pred);
}

template<class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value)
{
	for (; first != last; ++first)
		if (*first == old_value) *first = new_value;
}

template<class InputIterator, class OutputIterator, class T>
OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T& old_value, const T& new_value)
{
	for (; first != last; ++first, ++ result)
	{
		if (*first == old_value)
			*result = new_value;
		else
			*result = *first;
	}
	return result;
}

template<class ForwardIterator, class T, class Predicate>
void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& new_value)
{
	for (; first != last; ++first)
		if (pred(*first)) *first = new_value;
}

template<class InputIterator, class OutputIterator, class T, class Predicate>
OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, Predicate pred, const T& new_value)
{
	for (; first != last; ++first, ++ result)
	{
		if (pred(*first))
			*result = new_value;
		else
			*result = *first;
	}
	return result;
}

template <class Iterator, class OutputIterator, class Predicate, class T>
OutputIterator replace_copy_if(Iterator first, Iterator last, OutputIterator result, Predicate pred, const T& new_value) {
  for ( ; first != last; ++first, ++result)
    *result = pred(*first) ? new_value : *first;
  return result;
}

template<class BidirectionalIterator>
void __reverse(BidirectionalIterator first, BidirectionalIterator last, bidirectional_iterator_tag){
	while (true)
		if (first == last || first == --last)
			return;
		else iter_swap(first++, last);
}

template<class RandomAccessIterator>
void __reverse(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag){
	while (first < last) iter_swap(first++, --last);
}

template<class BidirectionalIterator>
inline void reverse(BidirectionalIterator first, BidirectionalIterator last){
	__reverse(first, last, iterator_category(first));
}

#endif