/** \file
***********************************************************************
* Storage for simple pointers. Implemented as AVL tree.
*
* $Id: ptrlist.c,v 1.1 2005/11/03 14:58:11 keinstein Exp $
* \author Tobias Schlemmer <keinstein@users.berlios.de>
* \date $Date: 2005/11/03 14:58:11 $
* \version $Revision: 1.1 $
*
* $Log: ptrlist.c,v $
* Revision 1.1  2005/11/03 14:58:11  keinstein
* initial release
*
*/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif
#ifdef HAVE_STRING_H
#  include <string.h>
#endif
#ifdef HAVE_STRINGS_H
#  include <strings.h>
#endif
#  include <stdio.h>
#include <assert.h>
#include "mutabor/bad_decl.h"
#include "mutabor/ptrlist.h"
#include "mutabor/ptrlist.hh"

/** Node type for AVL tree. */

struct mutabor_avl_node_ptr {
	struct mutabor_avl_node_ptr * left; /**< left successor */
	struct mutabor_avl_node_ptr * right; /**< right successor */
	const void * data; /**< Data */
	signed char balance; /**< For balancing the tree. */
};


void * MUTABOR_CLASS_FUNCTION(object,constructor)(void * _self);
void * MUTABOR_CLASS_FUNCTION(ptrlist,constructor)(void * _self)
{
	MUT_CLASS(ptrlist) * self;
	CHK_CLASS(_self,ptrlist);
	self = MUTABOR_CLASS_FUNCTION(object,constructor)(_self);
	self->root = NULL;
	return (_self);
}


static void delete_node (register struct  mutabor_avl_node_ptr * node )
{
	if (!node) return;
	if (node->left) delete_node (node->left);
	if (node->right) delete_node (node->right);
	free(node);
}

/** Destructor for class object. Does nothing than error checking. */

void * MUTABOR_CLASS_FUNCTION(object,destructor)(void * _self);
void * MUTABOR_CLASS_FUNCTION(ptrlist, destructor)(void * _self)
{
	MUT_CLASS(ptrlist) * self=_self;
	CHK_CLASS(_self,ptrlist);
	delete_node(self->root);
	return MUTABOR_CLASS_FUNCTION(object,destructor)(_self);
}


static char * print_node (register struct  mutabor_avl_node_ptr * node, register int depth)
{
	char *l=NULL, *r=NULL, *ret;
	if (node->left) l=print_node(node->left,depth+2);
	if (node->right) r=print_node(node->right,depth+2);
	if (asprintf(&ret,"+-%s\n%*c|%p (%d)\n%*c+-%s",l,
		     depth,' ',node->data,node->balance,depth,' ',r)) {
		if (l) free(l);
		if (r) free(r);
		return ret;
	}
	if (l) free(l);
	if (r) free(r);
	return NULL;
}

/** Formats Class content as string. Intented exspecially for debugging. */

char * MUTABOR_CLASS_FUNCTION(ptrlist,tostring)(void * _self)
{
	MUT_VIRTTABLE(object) ** self=_self;
	char * data, *tempstring;
	CHK_CLASS(_self,ptrlist);
	/* my data */
	if (!asprintf(&data,"%s (%p): %p\n--%s\n\n",
		      (*self)->name, 
		      (void *)*self,
		      _self,
		      tempstring=print_node (MUT_VALUE(ptrlist,_self)->root,2))){
		free(tempstring);
		return NULL;
	}
	free(tempstring);
	return data;
}


/** Search for an identifier in the list.
 * \param _self actual object.
 * \param pointer to be checked.
 * \return pointer to the first object or \c NULL if not found
 */
void * MUTABOR_CLASS_FUNCTION(ptrlist,find)(void const * _self, void const * ptr)
{
	MUT_CLASS(ptrlist) const *self=_self;
	struct  mutabor_avl_node_ptr * node=self->root;
	CHK_CLASS ( _self, ptrlist );
	if (!ptr) return NULL;
	while (node) {
		if (node->data < ptr) node=node->left;
		else
		if (node->data > ptr) node=node->right;
		else return node;
	}
	assert(!node);
	return NULL;
}



static void do_rotations(struct  mutabor_avl_node_ptr ** node2)
{
	struct  mutabor_avl_node_ptr * tmp;
	/* rotating */
	/* node2 should point to the pointer to the element which can have a |balance| = 2. */
	
	if ((*node2)->balance==-2) {
		if ((*node2)->left->balance ==1) { 
                        /* left-right rotation */
			tmp=( (*node2));
			( (*node2))=tmp->left->right;
			tmp->left->right=( (*node2))->left;
			( (*node2))->left=tmp->left;
			tmp->left=( (*node2))->right;
			( (*node2))->right=tmp;
			if ( (*node2)->balance == -1){
				(*node2)->left->balance=0;
				(*node2)->right->balance=0;
				(*node2)->balance=0;
			} else  if ( (*node2)->balance==1) {
				(*node2)->left->balance=-1;
				(*node2)->right->balance=-1;
				(*node2)->balance=0;
			}
		} else {
			tmp=( (*node2));
			( (*node2))=tmp->left;
			tmp->left=( (*node2))->right;
			( (*node2))->right=tmp;
			( (*node2))->balance=0;
			tmp->balance=0;
		}
	} else if (( (*node2))->balance== 2) {
		if (( (*node2))->left->balance==-1) {
			tmp=( (*node2));
			( (*node2))=tmp->right->left;
			tmp->right->left=( (*node2))->right;
			( (*node2))->right=tmp->right;
			tmp->right=( (*node2))->left;
			( (*node2))->left=tmp;
			if (( (*node2))->balance==-1){
				(*node2)->right->balance=0;
				(*node2)->left->balance=0;
				(*node2)->balance=0;
			} else  if ( (*node2)->balance==1) {
				(*node2)->right->balance=-1;
				(*node2)->left->balance=-1;
				(*node2)->balance=0;
			}
		} else {
			tmp=( (*node2));
			( (*node2))=tmp->right;
			tmp->right=( (*node2))->left;
			( (*node2))->left=tmp;
			( (*node2))->balance=0;
			tmp->balance=0;
		}
	}/*  else assert(!( (*node2))->balance); */
}

static signed char insert_ptr(struct mutabor_avl_node_ptr ** _node, const void * ptr) 
{
	struct  mutabor_avl_node_ptr ** node=_node,
		** last_non_balanced=_node;
	if (!ptr) return 0;
	if (!node) return 0;

	/* searching leaf in the AVL tree */

	while (*node) {
		if ((*node)->balance) last_non_balanced=node;
		if ((*node)->data < ptr) {
			node=&((*node)->left);
		}
		else if ((*node)->data > ptr) {
			node=&((*node)->right);
		}
		else return 0;
	}

	/* lets insert our ptr */

	(*node)=calloc(sizeof(struct  mutabor_avl_node_ptr),1);
	(*node) -> data = ptr;
	print_node (*node,0);
	
	/* update the data structures */
	node=last_non_balanced;
	while (*node) {
		if ((*node)->balance) last_non_balanced=node;
		if ((*node)->data < ptr) {
			assert((*node)->left);
			(*node)->balance--;
			node=&((*node)->left);
		}
		else if ((*node)->data > ptr) {
			assert((*node)->right);
			(*node)->balance++;
			node=&((*node)->right);
		}
		else {  /* inserted leaf (only for error checking */
			assert(!(*node)->left);
			assert(!(*node)->right);
			node=&((*node)->left);
		}
	}

	/* rotations */
	do_rotations(last_non_balanced);
	return 1;
}

/*
{
	struct mutabor_avl_node_ptr * node;
	if (node->data < ptr) {
		if (node->left) {
			int i;
			i = insert_ptr(&node->left,ptr);
			if (!i || i < -50) return i;
			node->balance -= i;
			if (node->balance == -2) {
				node->balance++;
				struct mutabor_avl_node_ptr * tmp = node -> left -> right;
				node->left->right=node;
				*_node = node->left;
				node->left=tmp;
				node->balance--;
			} else return node->balance ? 1 : 0;
		}
		else {
			node->left=calloc(sizeof(struct  mutabor_avl_node_ptr),1);
			node->left->data=ptr;
			if (--(node->balance)) return 1; else return 0;
		}
	} else if (node->data > ptr) {
		if (node->right) {
			int i = insert_ptr(&node->right,ptr);
			if (!i || i < -50) return i;
			node->balance += i;
			if (node->balance == 2) {
				node->balance--;
				struct mutabor_avl_node_ptr * tmp = node -> right -> left;
				node->right->left=node;
				*_node = node->right;
				node->right=tmp;
			} else return node->balance;
		}
		else {
			node->right=calloc(sizeof(struct  mutabor_avl_node_ptr),1);
			node->right->data=ptr;
			if (++(node->balance)) return 1; else return 0;
		}
	}
	else return -100;
}
*/

/** Insert an identifier in the list.
 * \param _self actual object.
 * \param identifier Identifier to be inserted.
 * \retval !=0 insert succeded
 * \retval 0 insert failed
 * 
 */

int MUTABOR_CLASS_FUNCTION(ptrlist,insert)(void * _self,const void * ptr)
{
	MUT_CLASS(ptrlist) *self=_self;
	if (!self->root) {
		self->root=calloc(sizeof(struct mutabor_avl_node_ptr),1);
		self->root->data=ptr;
		return 1;
	}
	return  insert_ptr(&self->root,ptr);
}




