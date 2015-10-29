#include "EZ_default_alloc_template.h"
#include "EZ_alloc.h"
#include "EZ_construct.h"

typedef __default_alloc_template<false, 0> alloc;

template<class T, class Alloc = alloc>
class simple_alloc{
public:
	typedef T			value_type;
	typedef T*			pointer;
	typedef const T*	const_pointer;
	typedef T&			reference;
	typedef const T&	const_reference;
	typedef size_t		size_type;
	typedef ptrdiff_t	difference_type;

	template<class U>
	struct rebind
	{
		typedef simple_alloc<U> other;
	};


	static pointer allocate(size_t n)
	{
		return 0 == n ? 0 : (T*)Alloc::allocate(n * sizeof(T));
	}

	static pointer allocate(void)
	{
		return 0 == n ? 0 : (T*)Alloc::allocate(sizeof(T));
	}

	static void deallocate(T *p, size_t n)
	{
		if (0 != n) Alloc::deallocate(p, n * sizeof(T));
	}

	static void deallocate(T *p)
	{
		if (0 != n) Alloc::deallocate(p, sizeof(T));
	}
};