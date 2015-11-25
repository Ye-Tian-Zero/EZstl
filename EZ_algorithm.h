#ifndef EZ_ALGORITHM_H
#define EZ_ALGORITHM_H

#include"EZ_iterator.h"
#include"EZ_pair_structure.h"
#include"__EZ_copy.h"
#include"EZ_heap.h"
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
count_if(InputIterator first, InputIterator last, Predicate pred)
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
Function for_each(InputIterator first, InputIterator last, Function f){
	for (; first != last; ++first)
		f(*first);
	return f;
}

template<class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen){
	for (; first != last; ++first)
		*first = gen();
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
			else if (!pred(*last))
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

template<class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result){
	while (first != last){
		--last;
		*(result++) = *last;
	}
	return result;
}

template<class ForwardIterator, class Distance>
void __rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Distance*, forward_iterator_tag){
	for (ForwardIterator i = middle;;){
		iter_swap(first, i);
		++first;
		++i;
		if (first == middle){
			if (i == last) return;
			middle = i;
		}
		else if (i == last)
			i = middle;
	}

}

template<class BidirectionalIterator, class Distance>
void __rotate(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Distance*, bidirectional_iterator_tag){
	reverse(first, middle);
	reverse(middle, last);
	reverse(first, last);
}

template<class ForwardIterator>
inline void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last){
	if (first == middle || middle == last)
		return;
	__rotate(first, middle, last, distance_type(first), iterator_category(first));
}

template<class ForwardIterator, class OutputIterator>
OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator result){
	return copy(first, middle, copy(middle, last, result));
}


template <class ForwardIterator1, class ForwardIterator2, class Distance1,
          class Distance2>
ForwardIterator1 __search(ForwardIterator1 first1, ForwardIterator1 last1,
                          ForwardIterator2 first2, ForwardIterator2 last2,
                          Distance1*, Distance2*) {
  Distance1 d1 = 0;
  d1 = distance(first1, last1);
  Distance2 d2 = 0;
  d2 = distance(first2, last2);

  if (d1 < d2) return last1;

  ForwardIterator1 current1 = first1;
  ForwardIterator2 current2 = first2;

  while (current2 != last2) 
    if (*current1 == *current2) {
      ++current1;
      ++current2;
    }
    else {
      if (d1 == d2)
        return last1;
      else {
        current1 = ++first1;
        current2 = first2;
        --d1;
      }
    }
  return first1;
}

template<class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1 search(ForwardIterator1 first1,
	ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2){
	return __search(first1, last1, first2, last2, distance_type(first1), distance_type(first2));
}

template <class ForwardIterator, class Integer, class T>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
                         Integer count, const T& value) {
  if (count <= 0)
    return first;
  else {
    first = find(first, last, value);
    while (first != last) {
      Integer n = count - 1;
      ForwardIterator i = first;
      ++i;
      while (i != last && n != 0 && *i == value) {
        ++i;
        --n;
      }
      if (n == 0)
        return first;
      else
        first = find(i, last, value);
    }
    return last;
  }
}

template <class ForwardIterator, class Integer, class T, class BinaryPredicate>
ForwardIterator search_n(ForwardIterator first, ForwardIterator last,
                         Integer count, const T& value,
                         BinaryPredicate binary_pred) {
  if (count <= 0)
    return first;
  else {
    while (first != last) {
      if (binary_pred(*first, value)) break;
      ++first;
    }
    while (first != last) {
      Integer n = count - 1;
      ForwardIterator i = first;
      ++i;
      while (i != last && n != 0 && binary_pred(*i, value)) {
        ++i;
        --n;
      }
      if (n == 0)
        return first;
      else {
        while (i != last) {
          if (binary_pred(*i, value)) break;
          ++i;
        }
        first = i;
      }
    }
    return last;
  }
} 

template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2){
	for (; firstr1 != last1; ++first1, ++first2)
		iter_swap(first1, first2);
	return first2;
}

template <class InputIterator, class OutputIterator, class UnaryOperation>
OutputIterator transform(InputIterator first, InputIterator last,
                         OutputIterator result, UnaryOperation op) {
  for ( ; first != last; ++first, ++result)
    *result = op(*first);
  return result;
}

template <class InputIterator1, class InputIterator2, class OutputIterator,
          class BinaryOperation>
OutputIterator transform(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, OutputIterator result,
                         BinaryOperation binary_op) {
  for ( ; first1 != last1; ++first1, ++first2, ++result)
    *result = binary_op(*first1, *first2);
  return result;
}


template <class InputIterator, class ForwardIterator>
ForwardIterator __unique_copy(InputIterator first, InputIterator last,
                              ForwardIterator result, forward_iterator_tag) {
  *result = *first;
  while (++first != last)
    if (*result != *first) *++result = *first;
  return ++result;
}


template <class InputIterator, class OutputIterator, class T>
OutputIterator __unique_copy(InputIterator first, InputIterator last,
                             OutputIterator result, T*) {
  T value = *first;
  *result = value;
  while (++first != last)
    if (value != *first) {
      value = *first;
      *++result = value;
    }
  return ++result;
}

template <class InputIterator, class OutputIterator>
inline OutputIterator __unique_copy(InputIterator first, InputIterator last,
                                    OutputIterator result, 
                                    output_iterator_tag) {
  return __unique_copy(first, last, result, value_type(first));
}

template <class InputIterator, class OutputIterator>
inline OutputIterator unique_copy(InputIterator first, InputIterator last,
                                  OutputIterator result) {
  if (first == last) return result;
  return __unique_copy(first, last, result, iterator_category(result));
}
template <class InputIterator, class ForwardIterator, class BinaryPredicate>
ForwardIterator __unique_copy(InputIterator first, InputIterator last,
                              ForwardIterator result, 
                              BinaryPredicate binary_pred,
                              forward_iterator_tag) {
  *result = *first;
  while (++first != last)
    if (!binary_pred(*result, *first)) *++result = *first;
  return ++result;
}

template <class InputIterator, class OutputIterator, class BinaryPredicate,
          class T>
OutputIterator __unique_copy(InputIterator first, InputIterator last,
                             OutputIterator result,
                             BinaryPredicate binary_pred, T*) {
  T value = *first;
  *result = value;
  while (++first != last)
    if (!binary_pred(value, *first)) {
      value = *first;
      *++result = value;
    }
  return ++result;
}

template <class InputIterator, class OutputIterator, class BinaryPredicate>
inline OutputIterator __unique_copy(InputIterator first, InputIterator last,
                                    OutputIterator result,
                                    BinaryPredicate binary_pred,
                                    output_iterator_tag) {
  return __unique_copy(first, last, result, binary_pred, value_type(first));
}

template <class InputIterator, class OutputIterator, class BinaryPredicate>
inline OutputIterator unique_copy(InputIterator first, InputIterator last,
                                  OutputIterator result,
                                  BinaryPredicate binary_pred) {
  if (first == last) return result;
  return __unique_copy(first, last, result, binary_pred,
                       iterator_category(result));
}

template <class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last) {
  first = adjacent_find(first, last);
  return unique_copy(first, last, first);
}

template <class ForwardIterator, class BinaryPredicate>
ForwardIterator unique(ForwardIterator first, ForwardIterator last,
                       BinaryPredicate binary_pred) {
  first = adjacent_find(first, last, binary_pred);
  return unique_copy(first, last, first, binary_pred);
}

template<class ForwardIterator, class T, class Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag)
{
	Distance len = 0;
	len = distance(first, last);
	Distance half;
	ForwardIterator middle;

	while (len > 0){
		half = len >> 1;
		middle = first;
		advence(middle, half);
		if (*middle < value){
			first = middle;
			++first;
			len = len - half - 1;
		}
		else
			len = half;
	}
	return first;
}

template<class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __lower_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value, Distance*, random_access_iterator_tag)
{
	Distance len = last - first;
	Distance half;
	RandomAccessIterator middle;

	while (len > 0){
		half = len >> 1;
		middle = first + half;
		if (*middle < value){
			first = middle + 1;
			len = len - half - 1;
		}
		else len = half;
	}
	
	return first;
}

template<class ForwardIterator, class T>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value){
	return __lower_bound(first, last, value, distance_type(first), iterator_category(first));
}

template<class ForwardIterator, class T, class Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag){
	Distance len = 0;
	distance(first, last, len);
	Distance half;
	ForwardIterator middle;

	while (len > 0)
	{
		half = len >> 1;
		middle = first;
		advance(middle, half);
		if (value < *middle)
			len = half;
		else{
			first = middle;
			++first;
			len = len - half - 1;
		}
	}
	return first;
}

template<class RandomAccessIterator, class T, class Distance>
RandomAccessIterator __upper_bound(RandomAccessIterator first, RandomAccessIterator last, const T& value, Distance*, random_access_iterator_tag){
	Distance len = last - first;
	Distance half;
	RandomAccessIterator middle;

	while (len > 0)
	{
		half = len >> 1;
		middle = first + half;
		if (value < *middle)
			len = half;
		else{
			first = middle + 1;
			len = len - half - 1;
		}
	}
	return first;
}

template<class ForwardIterator, class T>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value){
	return __upper_bound(first, last, value, distance_type(first), iterator_category(first));
}

template <class ForwardIterator, class T>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value){
	ForwardIterator i = lower_bound(first, last, value);
	if (*i == value && i != last)
		return true;
	return false;
}

template<class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last){
	if (first == last) return false;
	BidirectionalIterator i = first;
	++i;
	if (i == last) return false;
	i = last;
	--i;

	for (;;)
	{
		BidirectionalIterator ii = i;
		--i;
		if (*i < *ii){
			BidirectionalIterator j = last;
			while (!(*i < *--j));
			iter_swap(i, j);
			reverse(ii, last);
			return true;
		}
		if (i == first){
			reverse(first, last);
			return false;
		}
	}
}

template<class BidirectionalIterator>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last){
	if (first == last) return false;
	BidirectionalIterator i = first;
	++i;
	if (i == last) return false;
	i = last;
	--i;

	for (;;)
	{
		BidirectionalIterator ii = i;
		--i;
		if (*ii < *i){
			BidirectionalIterator j = last;
			while (!(*--j < *i));
			iter_swap(i, j);
			reverse(ii, last);
			return true;
		}
		if (i == first){
			reverse(first, last);
			return false;
		}
	}
}

template<class RandomAccessIterator>
inline void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last){
	__partial_sort(first, middle, last, value_type(first));
}

template<class RandomAccessIterator, class T>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, T*){
	make_heap(first, middle);
	for (RandomAccessIterator i = middle; i < last; ++i)
		if (*i < *first)
			__pop_heap(first, middle, i, T(*i), distance_type(first));
	sort_heap(first, middle);
}

template<class RandomAccessIterator, class T>
void __unguarded_linear_insert(RandomAccessIterator last, T value){
	RandomAccessIterator next = last;
	--next;
	while (value < *next){
		*last = *next;
		last = next;
		--next;
	}
	*last = value;
}

template<class ForwardIterator>
inline void __copy_backward(ForwardIterator src_end, ForwardIterator src_start, ForwardIterator dst)
{
	if (src_end == src_start)
		return;
	while (src_end != --src_start)
	{
		*(--dst) = *src_start;
	}
}

template<class RandomAccessIterator, class T>
inline void __linear_insert(RandomAccessIterator first, RandomAccessIterator last, T*){
	T value = *last;
	if (value < *first){
		__copy_backward(first, last, last + 1);
		*first = value;
	}
	else
		__unguarded_linear_insert(last, value);
}

template<class RandomAccessIterator>
void __insertion_sort(RandomAccessIterator first, RandomAccessIterator last)
{
	if (first == last) return;
	for (RandomAccessIterator i = first + 1; i != last; ++i)
		__linear_insert(first, i, value_type(first));
}

template<class T>
inline const T& __median(const T& a, const T& b, const T& c){
	if (a < b)
		if (b < c)
			return b;
		else if (a < c)
			return c;
		else
			return a;
	else if (a < c)
		return a;
	else if (b < c)
		return c;
	else
		return b;
}

template<class RandomAccessIterator, class T>
RandomAccessIterator __unguarded_partition(RandomAccessIterator first, RandomAccessIterator last, T pivot)
{
	while (true){
		while (*first < pivot) ++first;
		--last;
		while (pivot < *last) --last;
		if (!(first < last)) return first;
		iter_swap(first, last);
		++first;
	}
}

template<class Size>
inline Size __lg(Size n){
	Size k;
	for (k = 0; n > 1; n >>= 1)++k;
	return k;
}

template<class RandomAccessIterator, class T, class Size>
void __introsort_loop(RandomAccessIterator first, RandomAccessIterator last, T*, Size depth_limit)
{
	while (last - first > 16){
		if (depth_limit == 0){
			partial_sort(first, last, last);
			return;
		}
		--depth_limit;
		RandomAccessIterator cut = __unguarded_partition(first, last, T(__median(*first, *(first + (last - first) / 2), *(last - 1))));
		__introsort_loop(cut, last, value_type(first), depth_limit);
		last = cut;//It's not so good, I like '__introsort_loop(first, cut, value_type(first), depth_limit);'
	}
}

template<class RandomAccessIterator>
inline void __unguarded_insertion_sort(RandomAccessIterator first, RandomAccessIterator last){
	__unguarded_insertion_sort_aux(first, last, value_type(first));
}

template<class RandomAccessIterator , class T>
void __unguarded_insertion_sort_aux(RandomAccessIterator first, RandomAccessIterator last, T*){
	for (RandomAccessIterator i = first; i != last; ++i)
		__unguarded_linear_insert(i, T(*i));
}

template<class RandomAccessIterator>
void __final_insertion_sort(RandomAccessIterator first, RandomAccessIterator last){
	if (last - first > 16){
		__insertion_sort(first, first + 16);
		__unguarded_insertion_sort(first + 16, last);
	}
	else
		__insertion_sort(first, last);
}

template<class RandomAccessIterator>
inline void sort(RandomAccessIterator first, RandomAccessIterator last){
	if (first != last){
		__introsort_loop(first, last, value_type(first), __lg(last - first) * 2);
		__final_insertion_sort(first, last);
	}
}

#endif