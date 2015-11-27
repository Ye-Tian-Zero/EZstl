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

template<class Container>
class front_insert_iterator{
protected:
	Container* container;
public:
	typedef output_iterator_tag iterator_category;
	typedef void				volue_type;
	typedef void				difference_type;
	typedef void				pointer;
	typedef void				refference;

	explicit front_insert_iterator(Container& x) :container(&x){}

	front_insert_iterator<Container>& operator=(const typename Container::value_type& value){
		container->push_front(value);
		return *this;
	}

	front_insert_iterator<Container>& operator*(){ return *this; }
	front_insert_iterator<Container>& operator++(){ return *this; }
	front_insert_iterator<Container>& operator++(int){ return *this; }

};

template<class Container>
inline front_insert_iterator<Container> front_insert(Container& x){
	return front_insert_iterator<Container>(x);
}

template<class Container>
class back_insert_iterator{
protected:
	Container* container;
public:
	typedef output_iterator_tag iterator_category;
	typedef void				volue_type;
	typedef void				difference_type;
	typedef void				pointer;
	typedef void				refference;

	explicit back_insert_iterator(Container& x) :container(&x){}

	back_insert_iterator<Container>& operator=(const typename Container::value_type& value){
		container->push_back(value);
		return *this;
	}

	back_insert_iterator<Container>& operator*(){ return *this; }
	back_insert_iterator<Container>& operator++(){ return *this; }
	back_insert_iterator<Container>& operator++(int){ return *this; }

};

template<class Container>
inline back_insert_iterator<Container> back_insert(Container& x){
	return back_insert_iterator<Container>(x);
}

template<class Container>
class insert_iterator{
protected:
	Container* container;
	typename Container::iterator iter;
public:
	typedef output_iterator_tag iterator_category;
	typedef void				volue_type;
	typedef void				difference_type;
	typedef void				pointer;
	typedef void				refference;

	insert_iterator(Container& x, typename Container::iterator i) :container(&x), iter(i){}

	insert_iterator<Container>& operator=(const typename Container::value_type& value){
		iter = container->insert(iter, value);
		++iter;
		return *this;
	}

	explicit insert_iterator(Container& x) :container(&x){}

	insert_iterator<Container>& operator*(){ return *this; }
	insert_iterator<Container>& operator++(){ return *this; }
	insert_iterator<Container>& operator++(int){ return *this; }

};

template<class Container, class Iterator>
inline insert_iterator<Container> inserter(Container& x, Iterator i){
	typedef typename Container::iterator iter;
	return insert_iterator<Container>(x, iter(i));
}

template<class Iterator>
class reverse_iterator
{
protected:
	Iterator current;
public:
	typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
	typedef typename iterator_traits<Iterator>::value_type			value_type;
	typedef typename iterator_traits<Iterator>::difference_type		difference_type;
	typedef typename iterator_traits<Iterator>::pointer				pointer;
	typedef typename iterator_traits<Iterator>::reference			reference;

	typedef Iterator iterator_type;
	typedef reverse_iterator<Iterator> self;
public:
	reverse_iterator(){}
	explicit reverse_iterator(iterator_type x) :current(x){}
	reverse_iterator(const self& x) :current(x.current){}
	iterator_type base() const{ return current; }
	reference operator*() const{
		Iterator tmp = current;
		return *--tmp;
	}

	pointer operator->() const{ return &(operator*()); }

	self& operator++(){
		--current;
		return *this;
	}
	
	self operator++(int){
		Iterator tmp = current;
		--current;
		return tmp;
	}

	self& operator--(){
		++current;
		return *this;
	}

	self& operator--(int){
		Iterator tmp = current;
		++current;
		return tmp;
	}

	self operator+(difference_type n) const {
		return self(current - n);
	}

	self operator-(difference_type n) const {
		return self(current + n);
	}

	self& operator+=(difference_type n) const {
		current -= n;
		return *this;
	}

	self& operator-=(difference_type n) const {
		current += n;
		return *this;
	}
};

#endif