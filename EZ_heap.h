#ifndef EZ_HEAP_H
#define EZ_HEAP_H
#include"EZ_iterator.h"

template<class RandomAccessIterator, class Distance, class T>
inline void __push_heap(RandomAccessIterator first, Distance holeIndex, Distance topIndex, T val)
{
	Distance parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex && *(first + parent) < val)
	{
		*(first + holeIndex) = *(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(first + holeIndex) = val;
}

template<class RandomAccessIterator, class Distance, class T>
inline void __push_heap_aux(RandomAccessIterator first, RandomAccessIterator last, Distance*, T*)
{
	__push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last - 1)));
}

template<class RandomAccessIterator>
inline void push_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	__push_heap_aux(first, last, distance_type(first), value_type(first));
}

template<class RandomAccessIterator, class T, class Distance>
inline void __adjust_heap(RandomAccessIterator first, Distance holeIndex, Distance len, T value)
{
	Distance topIndex = holeIndex;
	Distance secondChildIndex = 2 * holeIndex + 2;
	while (secondChildIndex < len)
	{
		if (*(first + secondChildIndex) < *(first + (secondChildIndex - 1)))
			--secondChildIndex;

		*(first + holeIndex) = *(first + secondChildIndex);
		holeIndex = secondChildIndex;

		secondChildIndex = 2 * secondChildIndex + 2;
	}
	if (secondChildIndex == len)
	{
		*(first + holeIndex) = *(first + secondChildIndex - 1);
		holeIndex = secondChildIndex - 1;
	}
	__push_heap(first, holeIndex, topIndex, value);
}

template<class RandomAccessIterator, class T, class Distance>
inline void __pop_heap(RandomAccessIterator first, RandomAccessIterator last, RandomAccessIterator result, T value, Distance*)
{
	*result = *first;
	__adjust_heap(first, Distance(0), Distance(last - first), value);
}

template<class RandomAccessIterator, class T>
inline void __pop_heap_aux(RandomAccessIterator first, RandomAccessIterator last, T*)
{
	__pop_heap(first, last - 1, last - 1, T(*(last - 1)), distance_type(first));
}

template<class RandomAccessIterator>
inline void pop_heap(RandomAccessIterator first, RandomAccessIterator last){
	__pop_heap_aux(first, last, value_type(first));
}

template<class RandomAccessIterator>
void sort_heap(RandomAccessIterator first, RandomAccessIterator last){
	while (last - first > 1)
		pop_heap(first, last--);
}

template<class RandomAccessIterator, class T, class Distance>
void __make_heap(RandomAccessIterator first, RandomAccessIterator last, T*, Distance*)
{
	if (last - first < 2) return;
	Distance len = last - first;
	Distance parent = (len - 2) / 2;

	while (true){
		__adjust_heap(first, parent, len, T(*(first + parent)));
		if (parent == 0) return;
		parent--;
	}
}

template<class RandomAccessIterator>
inline void make_heap(RandomAccessIterator first, RandomAccessIterator last){
	__make_heap(first, last, value_type(first), distance_type(first));
}

#endif