/**
 *	Giuliano Sovernigo		0948924
 *	gsoverni@mail.uoguelph.ca
 *
 *	CIS*2520				A4: AVL
 *
 *	This file contains the code used to imliment an AVL tree that stores void pointers.
 *	The header file of the same name contains the definitions and comments for the 
 *	functions listed here.
 */

#include "treeLib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

TNode* makeNode(TNode* left, TNode* right, void* data)
{
	TNode* newNode;

	newNode = malloc(sizeof(TNode));
	if(newNode == NULL)
	{
		return NULL;
	}

	newNode->left = left;
	newNode->right = right;

	newNode->data = data;

	return newNode;
}

void destroyNode(TNode* TBD, void (*destroy)(void* data))
{
	if(TBD == NULL)
	{
		if(destroy == NULL) // essentially, this "cuts our losses", by at least freeing something
		{
			free(TBD->data);
		}
		else
		{
			destroy(TBD->data);
		}
	}
	free(TBD);
}

void* getData(TNode* node)
{
	if(node != NULL)
	{
		return node->data;
	}
	return NULL;
}

int operateOnData(TNode* node, int (*operate)(void* data))
{
	int result;
	if(getData(node) == NULL || operate == NULL) // note that getData also checks node for null.
	{
		return -1;
	}
	result = operate(getData(node));

	return result;
}

int preOrder(TNode* node, void (*action)(void*))
{
	int result;

	result = 0;
	if(node == NULL)
	{
		return 0;
	}
	if(action != NULL)
	{
		action(getData(node));
	}

	result += preOrder(node->left, action);
	result += preOrder(node->right, action);

	return 1 + result;
}

int inOrder(TNode* node, void (*action)(void*))
{
	int result;

	result = 0;
	if(node == NULL)
	{
		return 0;
	}
	result += inOrder(node->left, action);
	if(action != NULL)
	{
		action(getData(node));
	}
	result += inOrder(node->right, action);

	return 1 + result;
}

int postOrder(TNode* node, void (*action)(void*))
{
	int result;

	result = 0;
	if(node == NULL)
	{
		return 0;
	}
	result += postOrder(node->left, action);
	result += postOrder(node->right, action);
	if(action != NULL)
	{
		action(getData(node));
	}
	return 1 + result;
}

TNode* find(TNode* node, void* data, int (*compare)(void*,void*))
{
	if(node == NULL)
	{
		return NULL;
	}
	else if(compare(getData(node), data) == 0)
	{
		return node;
	}
	else
	{
		TNode* found;

		found = find(node->left, data, compare);
		if(found != NULL)
		{
			return found;
		}
		
		found = find(node->right, data, compare);
		if(found != NULL)
		{
			return found;
		}
	}
	return NULL;
}

void printAllMatchSpec(TNode* root, int (*matches)(void*, void*), void* mcond, void (*print)(void*))
{
	if(root == NULL)
	{
		return;
	}
	else if (matches == NULL || print == NULL)
	{
		return;
	}
	else if(matches(root->data,mcond) == 1)
	{
		print(root->data);
	}
	
	printAllMatchSpec(root->left, matches, mcond, print);
	printAllMatchSpec(root->right, matches, mcond, print);
}

int height(TNode* node)
{
	int heightl;
	int heightr;

	heightl = 0;
	heightr = 0;

	if(node == NULL)
	{
		return 0;
	}
	else
	{
		heightl = height(node->left);
		heightr = height(node->right);
	}
	
	if(heightl > heightr)
	{
		return 1 + heightl;
	}
	else
	{
		return 1 + heightr;
	}
	return 0;
}

int size(TNode* node)
{
	if(node == NULL)
	{
		return 0;
	}
	else
	{
		return 1 + size(node->left) + size(node->right);
	}	
	return -1;
}

int balanceFactor(TNode* node)
{
	int lHeight;
	int rHeight;

	if(node == NULL)
	{
		return 0;
	}

	lHeight = height(node->left);
	rHeight = height(node->right); 

	return rHeight - lHeight;
}

TNode* balance(TNode* root)
{
	int bfac;
	if(root == NULL)
	{
		return NULL;
	}

	if(root->left != NULL)
	{
		root->left = balance(root->left);
	}

	if(root->right != NULL)
	{
		root->right = balance(root->right);
	}

	bfac = balanceFactor(root);
	
	if(bfac > 1) // right heavy
	{
		if(balanceFactor(root->right) == -1)
		{
			root = rlRotate(root);
		}
		else
		{
			root = lRotate(root);
		}
	}
	else if(bfac < -1) // left heavy
	{
		if(balanceFactor(root->left) == 1)
		{
			root = lrRotate(root);
		}
		else
		{
			root = rRotate(root);
		}
	}
	return root;
}

TNode* rRotate(TNode* node)
{
	TNode* nRoot;

	if(node == NULL) // we cannot rotate nothing.
	{
		return NULL;
	}

	nRoot = node->left;
	node->left = nRoot->right;
	nRoot->right = node;

	return nRoot;
}

TNode* lRotate(TNode* node)
{
	TNode* nRoot;

	if(node == NULL)
	{
		return NULL;
	}

	nRoot = node->right;
	node->right = nRoot->left;
	nRoot->left = node;

	return nRoot;
}

TNode* rlRotate(TNode* node)
{
	if(node == NULL)
	{
		return NULL;
	}
	node->right = rRotate(node->right);
	return lRotate(node);
}

TNode* lrRotate(TNode* node)
{
	if(node == NULL)
	{	
		return NULL;
	}
	node->left = lRotate(node->left);
	return rRotate(node);
}

TNode* add(TNode* tree, TNode* node, int (*compare)(void*,void*), void (*equalAction)(void*))
{
	int diff;

	if(node == NULL || getData(node) == NULL)
	{
		return tree;
	}
	else if(tree == NULL || getData(tree) == NULL)
	{
		return node;
	}	

	diff = compare(getData(tree), getData(node));

	if(diff == 0)
	{
		if(equalAction != NULL)
		{
			equalAction(getData(tree));
		}		
		return tree;
	}
	else if(diff > 0) // node belongs SOMEWHERE left of tree
	{
		if(tree->left == NULL)
		{
			tree->left = node;
		}
		else
		{
			tree->left = add(tree->left, node, compare, equalAction);
		}
		return balance(tree);
	}
	else if(diff < 0) // node belongs SOMEWHERE right of tree.
	{
		if(tree->right == NULL) // we can just add
		{
			tree->right = node;
		}
		else
		{
			tree->right = add(tree->right, node, compare, equalAction);
		}
		return balance(tree);
	}

	return tree;
}

TNode* tRemove(TNode* tree, void* data, int (*compare)(void*,void*))
{
	if(tree == NULL)
	{
		return NULL;
	}

	if(compare(getData(tree), data) == 0)
	{
		if(tree->left == NULL && tree->right == NULL)
		{
			return NULL;
		}
		else if(tree->left == NULL || tree->right == NULL)
		{
			if(tree->left == NULL)
			{
				return tree->right;
			}
			else
			{
				return tree->left;
			}
		}
		else
		{
			int lheight;
			int rheight;

			lheight = height(tree->left);
			rheight = height(tree->right);

			if(lheight > rheight)
			{
				TNode* lchild;
				lchild = tree->left;
				while(lchild->right != NULL)
				{
					lchild = lchild->right;
				}
				tRemove(tree->left, getData(lchild), compare);
				lchild->left = tree->left;
				lchild->right = tree->right;
				return balance(lchild);
			}
			else
			{
				TNode* lchild;
				lchild = tree->right;
				while(lchild->left != NULL)
				{
					lchild = lchild->left;
				}
				tRemove(tree->right, getData(lchild), compare);
				lchild->left = tree->left;
				lchild->right = tree->right;
				return balance(lchild);
			}
		}
	}
	else
	{
		tree->left = tRemove(tree->left, data, compare);
		tree->right = tRemove(tree->right, data, compare);
	}
	
	return balance(tree);

}

int printTree(TNode* tree, int level, void (*print)(void*))
{
	int i;

	for(i = 0; i < level; i++)
	{
		printf("|    ");
	}
	printf("\n");
	for(i = 0; i < level; i++)
	{
		printf("|    ");
	}
	printf("\n");

	for(i = 0; i < level-1; i++)
	{
		printf("|    ");
	}

	if(level != 0 )
	{
		printf("====="); // print the sub-item branch.
	}

	if(tree == NULL)
	{
		printf("NULL NODE");
	}
	else
	{
		print(getData(tree));	
	}
	printf(":%d\n",balanceFactor(tree));

	if(tree != NULL) // if we have a left child
	{
		printTree(tree->left, level + 1, print);
		printTree(tree->right, level + 1, print);
	}

	return 0;
}


void destroyTree(TNode* root, void (*destroy)(void*))
{
	if(root == NULL || destroy == NULL);
	{
		return;
	}
	destroyTree(root->left,destroy);
	destroyTree(root->right,destroy);
	destroyNode(root,destroy);
	return;
}

