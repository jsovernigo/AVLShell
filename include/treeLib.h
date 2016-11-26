
/**
 *	Giuliano Sovernigo		0948924
 *	gsoverni@mail.uoguelph.ca
 *
 *	CIS*2520				A4: AVL
 *
 *	This file contains definitions for common methods used in avl tree 
 *	creation and maintenance.  The code for these is found in the cfile
 *	of the same name.
 */
#ifndef __GSOVERNIGO_TREELIB_H__
#define __GSOVERNIGO_TREELIB_H__

struct tree_node
{
	void* data;
	struct tree_node* left;
	struct tree_node* right;
};

typedef struct tree_node TNode;


/**
 *	makeNode
 *	makes a new TNode pointer that can be used to impliment a new TreeNode.
 *	IN:			parent		- the parent of the new node
 *				left		- the new left child of the new node.
 *				right		- the new right child of the new node.
 *				data		- the new data for the new node.
 *	OUT:		a new TNode that will have parent parent, left left, right 
 *				right, and data data.
 *	POST:		a new TNode has been allocated, and should be deallocated
 *				using the destroyNode function.
 *  ERROR:		malloc fails to produce valid memory.
 */
TNode* makeNode(TNode* left, TNode* right, void* data);

/**
 *	destroyNode
 *	destroys a node, and frees its data
 *	IN:			TBD			- the node to be destroyed
 *	   			destroy		- a function pointer to a function that can 
 *							  successfully operate on the void data of the node
 *	OUT:		void, no return.
 *	POST:		TBD has been deallocated, and should be handled with care.
 *	ERROR:		destroy is NULL.
 */
void destroyNode(TNode* TBD, void (*destroy)(void* data));

/**
 *	getData
 *	returns the data that is contained in the node (void pointer)
 *	IN:			node		- a node that will have its data returned to caller
 *	OUT:		the data member of the node, node.
 *	POST:		a void pointer has been returned.
 *	ERROR:		node is null, or node->data is a dangling pointer.
 */
void* getData(TNode* node);

/**
 *	operateOnData
 *	pass in a function pointer that will operate non-destructively on node's
 *	data.  Destructive functions can result in undefined behaviour in the tree.
 *	IN:			node		- the node that will have its data operated on.
 *				operate		- a integer-returning function pointer that will
 *							  operate on the data in the node.
 *	OUT:		an integer representing the return of operate.
 *	POST:		node->data could have been operated on.
 *	ERROR:		node or operate are null
 */
int operateOnData(TNode* node, int (*operate)(void* data));

/**
 *	preOrder
 *	traverses the tree in preorder order, operating on each node using action.
 *	IN:			node		- the node that will be treated as the root.
 *				action		- the function pointer that will contain code to
 *							  operate on the data of each node.
 *	OUT:		0 on success, negative error code on failure
 *	POST:		action has been performed on all nodes' data
 *	ERROR:		node or action is null
 */
int preOrder(TNode* node, void (*action)(void*));

/**
 *	inOrder
 *	traverses the tree in inorder order, operating on each node using action.
 *	IN:			node		- the node that will be treated as the root.
 *				action		- the function pointer that will contain code to
 *							  operate on the data of each node.
 *	OUT:		0 on success, negative error code on failure
 * 	POST:		action has been performed on all nodes' data
 * 	ERROR:		node or action is null
 */
int inOrder(TNode* node, void (*action)(void*));

/**
 *	postOrder
 *	traverses the tree in postorder order, operating on each node using action.
 *	IN:			node		- the node that will be treated as the root.
 *				action		- the function pointer that will contain code to
 *							  operate on the data of each node.
 *	OUT:		0 on success, negative error code on failure
 * 	POST:		action has been performed on all nodes' data
 * 	ERROR:		node or action is null
 */
int postOrder(TNode* node, void (*action)(void*));

/**
 *	find
 *	finds a node that contains the match to data
 *	IN:			node		- the node that we are operating on
 *				data		- the data that must be matched to be returned
 *				compare		- a function pointer to the compare the data nodes
 *	OUT:		the first node found that validates compare for data, node->data
 *	POST:		a node has been returned
 *	ERROR:		anything is NULL.
 */
TNode* find(TNode* node, void* data, int (*compare)(void*,void*));


/**
 *	printAllMatchSpec
 *	prints all nodes which conform to the return of integer 1 in matches. mcond
 *	is the void* that root->data must conform to, according, again to matches.
 *	IN:			root		- the root node that we are CURRENTLY operating on
 *				matches		- a function pointer that acts similar to the 
 *							  compare function, but returns 1 should root->data
 *							  conform to mcond in a predefined manner.
 *				mcond		- the other void pointer that "matches" the root
 *							  data.
 *				print		- the function pointer to the print function.
 *	OUT:		void
 *	POST:		all data in the tree conforming to mcond has been printed to
 *				stdout.
 *	ERROR:		where do I start... anything is null.
 */
void printAllMatchSpec(TNode* root, int (*matches)(void*, void*), void* mcond, void (*print)(void*));

/**
 *	height
 *	calculates the height of the tree, returning the largest possible height.
 *	IN:			node		- root node to be measured.
 *	OUT:		the height, in integer form, that was calculated.
 *	POST:		integer returned to caller.
 *	ERROR:		node is null, -1 returned.
 */
int height(TNode* node);

/**
 *	size
 *	returns the size of the tree.  All nodes.
 *	IN:			node		- the node we are operating on.
 *	OUT:		an integer size of the whole tree.
 *	POST:		an integer has been returned
 *	ERROR:		node is null
 */
int size(TNode* node);

/**
 *	balanceFactor
 *	calculates and returns the difference between the height of the left and
 *	right subtrees, such that the left tree's height is subtracted from that
 *	of the right, to produce an integer difference.
 *	IN:			node		- the node to be checked for balance
 *	OUT:		an integer representing the balance factor of node
 *	POST:		an integer has been returned.
 *	ERROR:		node is null. 
 */
int balanceFactor(TNode* node);

/**
 *	balance
 *	balances the whole tree, so as to cause it to be most efficient for binary
 *	search algorithms and generally more efficient in all operation aspects.
 *	IN:			root		- the root node that will be balanced
 *	OUT:		the new root, should a super drastic change occur.
 *	POST:		root's structure could have changed.
 *	ERROR:		root is null, or is in someway inaccessable. (dangling pointer)
 */
TNode* balance(TNode* root);

/**
 *	rRotate
 *	rotates node once in the rightward direction.
 *	IN:			node		- the node that will be balanced.
 *	OUT:		the new node that is now in node's old position (rotated child)
 *	POST:		the structure of node and its tree are... different now.
 *	ERROR:		node is null or cannot be rotated.
 *	REF:		Information and concepts for rotations taken from:
 *				http://emunix.emich.edu/~haynes/Papers/AVL/rotations.pdf	
 */
TNode* rRotate(TNode* node);

/**
 *	lRotate
 *	rotates node once in the leftward direction.
 *	IN:			node 		- the node to be balanced.
 *	OUT:		the node that has taken node's place.
 *	POST:		the structure that is returned is different from node's
 *	ERROR:		node is null
 *	REF:		Information and concepts for rotations taken from:
 *				http://emunix.emich.edu/~haynes/Papers/AVL/rotations.pdf	
 */
TNode* lRotate(TNode* node);

/**
 *	rlRotate
 *	rotates the node->left right, then node left.
 *	IN:			node		- the node we are to rotate.
 *	OUT:		return the rotated node
 *	POST:		the node has been rotated
 *	ERROR:		node is null or can NOT BE ROTATED RL (WILL segfault)
 *	REF:		Information and concepts for rotations taken from:
 *				http://emunix.emich.edu/~haynes/Papers/AVL/rotations.pdf
 */
TNode* rlRotate(TNode* node);

/**
 * 	lrRotate
 *	rotates node->right, then node right.
 *	IN:			node		- the node we can operate on.
 *	OUT:		returns the properly rotated node.
 *	POST:		node has been rotated
 *	ERROR:		node is null or CANNOT BE ROTATED LR (WILL segfault)
 *  REF:		Information and concepts for rotations taken from:
 *				http://emunix.emich.edu/~haynes/Papers/AVL/rotations.pdf
 */
TNode* lrRotate(TNode* node);

/**
 *	add
 *	adds node to tree, using compare to sort them, and equalaction,
 *	should the node already exist.
 *	IN:			tree		- the tree that will be added TO.
 *				node		- the node that will be ADDED
 *				compare		- the comparison function that wll be used
 *				equalAction	- the function that outlines actions to be taken if
 *							  the node is already existant.
 *	OUT:		The balanced tree's root.
 *	POST:		node has been added to tree, and tree has been balanced.
 *	ERROR:		anything is null
 */
TNode* add(TNode* tree, TNode* node, int (*compare)(void*,void*), void (*equalAction)(void*));

/**
 * 	tRemove
 * 	removes the node containing data from the tree.
 *  IN:			tree		- the tree to be trimmed.
 *  			data		- that data we are searching for
 *  			compare		- the function that returns 0 if equal
 *  OUT:		the tree, with the node containing data removed.
 *  POST:		tree should be 1 node smaller.
 *  ERROR:		anything is null.
 */
TNode* tRemove(TNode* tree, void* data, int (*compare)(void*, void*));

/**
 *	printTree
 *	prints the tree to the screen, in the style of a file tree.
 *	*NOTE*
 *		-This function is purely for debugging purposes.  Do not use it for
 *		normal operation.
 *	IN:			tree		- the tree to be printed
 *				level		- the level of the current node (call with 0)
 *				print		- function pointer specification for printing
 *							  tree->data
 *	OUT:		0 on success.
 *	POST:		tree has been printed to stdout
 *	ERROR:		print is null.
 */
int printTree(TNode* tree, int level, void (*print)(void*));

/**
 *	destroyTree
 *	destroys and deallocates all tree nodes and their respective data to free
 *	the space used up by the tree for further allocationa and circulation.
 *	IN:			root		- the root of your tree.
 *				destroy		- a function pointer that free root->data properly.
 *	OUT:		void; why would I return anything? duh.
 *	POST:		the tree root has been deallocated and should be treated with
 *				the utmost caution.  NO TOUCHING.
 *  ERROR:		destroy is null.
 */
void destroyTree(TNode* root, void (*destroy)(void*));

#endif
