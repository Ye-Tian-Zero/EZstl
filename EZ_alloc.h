#ifndef EZ_ALLOC_H
#define EZ_ALLOC_H

#if 0
#	include<new>
#	define __THROW_BAD_ALLOC throw bad_alloc
#elif	!defined(__THROW_BAD_ALLOC)
#	include<iostream>
#	define __THROW_BAD_ALLOC std::cerr << "out of memory" << std::endl; exit(1)
#endif

template<int inst>
class __malloc_alloc_template
{
private:
	static void *oom_malloc(size_t);
	static void *oom_realloc(void*, size_t);
	static void(*_malloc_alloc_oom_handler)();
public:
	static void *allocate(size_t n)
	{
#ifdef DEBUG
		std::cout << "first level allocator: " << n << " bytes." << std::endl;
#endif
		void *result = malloc(n);
		if (0 == result) result = oom_malloc(n);
		return result;
	}

	static void deallocate(void *p, size_t/*n*/)
	{
		free(p);
	}

	static void* reallocate(void* p, size_t/*old_sz*/, size_t new_sz)
	{
		void *result = realloc(p, new_sz);
		if (0 == result) result = oom_realloc(p, new_sz);
		return result;
	}

	static void(*set_malloc_handler(void(*f)()))()
	{
		void(*old)() = __malloc_alloc_oom_handler;
		__malloc_alloc_oom_handler = f;
		return old;
	}

};

template<int inst>
void(*__malloc_alloc_template<inst>::_malloc_alloc_oom_handler)() = nullptr;

template<int inst>
void *__malloc_alloc_template<inst>::oom_malloc(size_t n)
{
	void (*my_malloc_handler)();
	void * result;
	for (;;)
	{
		my_malloc_handler = _malloc_alloc_oom_handler;
		if (0 == my_malloc_handler) { __THROW_BAD_ALLOC; }
		(*my_malloc_handler)();
		result = malloc(n);
		if (result) return result;
	}
}//If _malloc_alloc_oom_handler have been set, try it infinitely. Else throw exception;

template<int inst>
void *__malloc_alloc_template<inst>::oom_realloc(void *p, size_t n)
{
	void (*my_malloc_handler)();
	void *result;
	for (;;)
	{
		my_malloc_handler = _malloc_alloc_oom_handler;
		if (0 == my_malloc_handler){ __THROW_BAD_ALLOC; }
		(*my_malloc_handler)();
		result = realloc(n);
		if (result) return result;
	}
}

typedef __malloc_alloc_template<0> malloc_alloc;

#endif