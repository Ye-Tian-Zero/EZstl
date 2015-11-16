#ifndef EZ_ITERATOR_H
#define EZ_ITERATOR_H
#include<cstddef>
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag{};
struct random_access_iterator_tag : public bidirectional_iterator_tag{};

template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
class iterator{
	typedef Category	iterator_category;
	typedef T			value_type;
	typedef Distance	diff_type;
	typedef Pointer		pointer;
	typedef Reference	reference;
};

template <class Iterator>
struct iterator_traits{
	typedef typename Iterator::value_type			value_type;
	typedef typename Iterator::reference			reference;
	typedef typename Iterator::pointer				pointer;
	typedef typename Iterator::difference_type		difference_type;
	typedef typename Iterator::iterator_category	iterator_category;
};

template <class T>
struct iterator_traits<T*> {
	typedef T							value_type;
	typedef T&							reference;
	typedef T*							pointer;
	typedef ptrdiff_t					difference_type;
	typedef random_access_iterator_tag	iterator_category;
};

template <class T>
struct iterator_traits < const T* > {
	typedef T							value_type;
	typedef const T&					reference;
	typedef const T*					pointer;
	typedef ptrdiff_t					difference_type;
	typedef random_access_iterator_tag	iterator_category;
};

template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&)
{
	return typename iterator_traits<Iterator>::iterator_category();
}

template<class Iterator>
inline typename iterator_traits<Iterator>::value_type* value_type(const Iterator&)
{
	return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

template <class input_iterator>
inline typename iterator_traits<input_iterator>::difference_type* distance_type(const input_iterator&)
{
	return static_cast< typename iterator_traits<input_iterator>::difference_type* >(0);
}

template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type 
__distance(InputIterator first, InputIterator last, input_iterator_tag)
{
	typename iterator_traits<InputIterator>::difference_type n = 0;
	while (first != last)
	{
		++first; ++n;
	}
	return n;
}

template <class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type 
__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
{
	typename iterator_traits<RandomAccessIterator>::difference_type n = 0;
	return last - first;
}

//need test
template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type 
distance(InputIterator first, InputIterator last)
{
	return __distance(first, last, iterator_category(first));
}

template<class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag)
{
	while (n--)
	{
		++i;
	}
}

template<class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
{
	if (n >= 0)
		while (n--) ++i;
	else
		while (n++)	--i;
}

template<class RandomAccessIterator, class Distance>
inline void __advance(RandomAccessIterator& i, Distance n, random_access_iterator_tag)
{
	i += n;
}

template<class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n)
{
	__advance(i, n, iterator_category(i));
}
#endif