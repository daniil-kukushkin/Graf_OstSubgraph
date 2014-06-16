#pragma once

#include "Edge.h"

struct Node{
	Edge* data;
	int key;
	Node* left, *right, *parent;
	Node()
	{
		left = right = parent = nullptr;
	}
};

class Tree_{
	Node* root;

	void insert_(Node* x, Node* z)
	{
		if(z->key > x->key)
		{
			if(x->right != nullptr)
				insert_(x->right, z);
			else
			{
				z->parent = x;
				x->right = z;
			}
		} else
			if(x->left != nullptr)
				insert_(x->left, z);
			else
			{
				z->parent = x;
				x->left = z;
			}
	}

	Node* next(Node* x)
	{
		Node* y;
		if(x->right != nullptr)
			return minimum_(x->right);
		y = x->parent;
		while(y != nullptr && x == y->right)
		{
			x = y;
			y = y->parent;
		}
		return y;
	}

	Node* minimum_(Node* x)
	{
		if(x->left == nullptr)
			return x;
		return minimum_(x->left);
	}

public:
	int count;
	Tree_()
	{
		root = nullptr;
		count = 0;
	}

	void deleteNode(Node* z) 				
	{
		count--;
		Node *x, *y;						
		if(z->left != nullptr && z->right != nullptr)			
		{
			y = next(z);				
			x = nullptr;
			if(y == y->parent->left)
				y->parent->left = nullptr;
			else
			{
				y->parent->right = nullptr;
				z->key = y->key;				
				z->data->v1 = y->data->v1;
				z->data->v2 = y->data->v2;
			}
		}
		else 
		if(z->left != nullptr || z->right != nullptr)		
		{
			y = z;						
			if(y->left != nullptr)		
				x = y->left;			
			else
				x = y->right;
		} else {						
			y = z;				
			x = nullptr;
		}
		if( x != nullptr)
			x->parent = y->parent;	

		if (y->parent == nullptr)
			root = x;
		else
			if (y == y->parent->left)
				y->parent->left = x;
			else
			y->parent->right = x;
	}

	void insert(Edge* e, int w)
	{
		count++;
		Node* newNode = new Node();
		newNode->data = e;
		newNode->key = w;
		if(root == nullptr)
			root = newNode;
		else
			insert_(root, newNode);
	}

	Node* minimum()
	{
		return minimum_(root);
	}
	

};















/*
template<class T> class TreeNode_ {
protected:
	TreeNode_  *_lchild;
	TreeNode_  *_rchild;
	Т val;
public:
	TreeNode_(T);
};

template<class T> TreeNode_<T>::TreeNode_(T v) :
val(v), _lchild(NULL), _rchild (NULL)
{
}

template<class T> class SearchTree_ {
private:
	TreeNode_ *root;
	TreeNode_<T> *_findMin(TreeNode_<T> *);
	void _remove(T, TreeNode_<T> * &);
	void _inorder(TreeNode_<T> *);
public:
	SearchTree_ ();
	int isEmpty (void);
	Т find(T);
	Т findMin(void);
	void inorder (void(*) (T) );
	void insert(T);
	void remove(T);
	T removeMin (void);
};

template<class T> SearchTree_<T>::SearchTree_ (int (*с) (Т, Т) ) :
cmp(с), root (NULL)
{
}

template<class T> int SearchTree_<T>::isEmpty (void)
{
	return (root == NULL);
}


template<class T> SearchTree_<T>::~SearchTree_ (void)
{
	if (root) delete root;
}

template<class T> T SearchTree_::find (T val)
{
	TreeNode_ *n = root;
	while (n) {
		int result = (*cmp) (val, n->val);
		if (result < 0)
			n = n->_lchild;
		else if (result > 0)
			n = n->_rchild;
		else
			return n->val;
	}
	return  NULL;
}

template<class T> T SearchTree_<T>::findMin (void)
{
	TreeNode_<T> *n = _findMin (root);
	return (n ? n->val : NULL);
}

template<class T>
TreeNode_<T> *SearchTree_<T>::_findMin (TreeNode_<T> *n)
{
	if (n  == NULL)
		return NULL;
	while   (n->_lchild)
		n = n->_lchild;
	return n;
}

template<class T> void SearchTree_<T>::inorder (void (*visit)    (Т) )
{
	_inorder (root, visit);
}

template<class T>
void SearchTree_::inorder (TreeNode_<T> *n, void(*visit) (T) )
{
	if (n) {
		_inorder (n->_lchild, visit);
		(*visit) (n->val);
		_inorder (n->_rchild, visit);
	}
}

template<class T> void SearchTree_<T>::insert(T val)
{
	if (root == NULL) {
		root = new TreeNode_<T>(val);
		return;
	} else {
		int result;
		TreeNode_<T> *p, *n = root;
		while (n) {
			p = n;
			result = (*cmp) (val, p->val);
			if (result < 0)
				n = p->_lchild;
			else if (result > 0)
				n = p->_rchild;
			else
				return;
		}
		if (result < 0)
			p->_lchild = new TreeNode_<T>(val);
		else
			p-> rchild = new TreeNode_<T>(val);
	}
}

template<class T> 
void SearchTree_ <T>::remove(Т val)
{
	_remove(val, root); 
}

template<class T>
void SearchTree_<T>::_remove(Т val, TreeNode_<T> * &n)
{
	if (n == NULL)
		return;
	int result = (*cmp) (val, n->val);
	if (result < 0)
		_remove(val, n->_lchild);
	else if (result > 0)
		_remove (val, n->_rchild);
	else {                              // случай 1
		if (n->_lchild == NULL) {
			TreeNode_<T> *old = n;
			n = old->_rchild;
			delete old;
		}
		else if (n->_rchild == NULL {     // случай 2
			TreeNode_<T> *old = n;
			n = old->_lchild;
			delete old;
		}
		else {	                          // случай 3
			TreeNode_<T> *m = _findMin(n->_rchild);
			n->val = m->val;
			remove(m->val, n->_rchild);
		}
	}
}

template<class Т> Т SearchTree_<T>::removeMin (void)
{
	Т v = findMin();
	remove (v);
	return v;
}

/*
#include "TreeNode_.h"

template <class T> class Tree
{
public:
	Tree();                                                    
	int insert_node( T &);                        
	TreeNode__<T>* delete_node(TreeNode__<T> *);
	TreeNode__<T>* find_max(TreeNode__<T>*);                                                               
	TreeNode__<T>* find_min(TreeNode__<T>*);
	TreeNode__<T>* find_node(TreeNode__<T>*, T &);
	TreeNode__<T>* find_succsessor( T &);    
	TreeNode__<T> *get_root();   
	int count;
private:
	TreeNode__<T> *root;                                  
};

template<class T> Tree<T>::Tree()
{
	root=0;  
	count = 0;
}

template<class T> int Tree<T>::insert_node( T &x)
{
	TreeNode__<T>* n=new TreeNode__<T>(x);  
	TreeNode__<T>* ptr;
	TreeNode__<T>* ptr1;

	n->parent=n->left=n->right=0;         
	ptr=root;
	while(ptr!=0)                    
	{
		ptr1=ptr;                
		if(x < ptr->get_data() ) 
			ptr=ptr->left;
		else
			ptr=ptr->right;   
	}
	n->parent=ptr1;
	if(ptr1==0)                    
		root=n;
	else
	{
		if(x < ptr1->get_data() )
			ptr1->left=n;
		else
			ptr1->right=n;
	}
	count++;
	return 0;
}


template<class T> TreeNode__<T>* Tree<T>::delete_node(TreeNode__<T> *z)
{
	TreeNode__<T>* y;
	TreeNode__<T>* x;
	if(z->left == 0 || z->right == 0)               
		y=z;
	else
		y=find_succsessor(z->get_data());
	if(y->left!=0)                                
		x=y->left;
	else
		x=y->right;
	if(x!=0)                                        
		x->parent=y->parent;
	if(y->parent == 0)
		root=x;
	else
	{
		if (y== (y->parent)->left)
			(y->parent)->left=x;
		else
			(y->parent)->right=x;
	}
	if(y!=z)                                        
		z->data=y->get_data();
	count--;
	return y;
}
template<class T> TreeNode__<T>* Tree<T>::find_max(TreeNode__<T>* x)
{
	while(x->right!=0)                              
		x=x->right;
	return x;
}

template<class T> TreeNode__<T>* Tree<T>::find_min(TreeNode__<T>* x)
{
	while(x->left!=0)
		x=x->left;
	return x;
}

template<class T> TreeNode__<T>* Tree<T>::find_succsessor( T & val)
{
	TreeNode__<T>* x=find_node(root,val);                    
	TreeNode__<T>* y;
	if(x == 0)
		return 0;
	if(x->right!=0)                                             
		return find_min(x->right);
	y=x->parent;
	while(y!=0 && x == y->right)                                  
	{
		x=y;
		y=y->parent;
	}
	return y;
}

template<class T> TreeNode__<T>* Tree<T>::find_node(TreeNode__<T>* n,
	 T & val)
{
	if(n==0 || val==n->get_data())
		return n;
	if(val > n->get_data() )
		return find_node(n->right,val);
	else
		return find_node(n->left,val);
}

template<class T> TreeNode__<T>* Tree<T>::get_root()
{
	return root;
}
*/