#ifndef EZ_RB_TREE_H
#define EZ_RB_TREE_H

#include"EZ_iterator.h"

typedef bool __rb_tree_color_type;
const __rb_tree_color_type __rb_tree_red = false;
const __rb_tree_color_type __rb_tree_black = true;

struct __rb_tree_node_base{
	typedef __rb_tree_color_type color_type;
	typedef __rb_tree_node_base* base_ptr;

	color_type color;
	base_ptr parent;
	base_ptr left;
	base_ptr right;

	static base_ptr minimum(base_ptr x){
		while (x->left != 0) x = x->left;
		return x;
	}

	static base_ptr maximum(base_ptr x){
		while (x->right != 0) x = x->right;
		return x;
	}
};

template <class value>
struct __rb_tree_node : public __rb_tree_node_base 
{
	typedef __rb_tree_node<value>* link_type;
	value value_field;
};


struct __rb_tree_iterator_base
{
	typedef typename __rb_tree_node_base::base_ptr	base_ptr;
	typedef bidirectional_iterator_tag				iterator_category;
	typedef ptrdiff_t								difference_type;

	base_ptr node;

	void increment()
	{
		if (node->right != 0){
			node = node->right;
			while (node->left != 0)
				node = node->left;
		}
		else{
			base_ptr pa = node->parent;
			while (node == pa->right)
			{
				node = pa;
				pa = pa->parent;
			}
			if (node->right != pa)
				node = pa; //WTFFFFFFFFFFFFFFFFFFFFFFFFFF!F!!!!!!!!!!!!!!
		}
	}

	__rb_tree_node_base* node;
	void increment();
	void decrement();
};

template<T, R, P> struct
__rb_tree_iterator
{
	typedef __rb_tree_node<T>* link_type;
};

#endif