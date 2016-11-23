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

void destroyData(TNode* TBD, void (*destroy)(void* data))
{
	if(TBD == NULL)
	{
		if(destroy == NULL)
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
		if(balanceFactor(root->right) < 0)
		{
			root->right = rRotate(root->right);
		}
		root = lRotate(root);
	}
	else if(bfac < -1) // left heavy
	{
		if(balanceFactor(root->left) > 0)
		{
			root->left = lRotate(root->left);
		}
		root = rRotate(root);
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

TNode* add(TNode* tree, TNode* node, int (*compare)(void*,void*), void (*equalAction)(void*))
{
	int diff;

	if(node == NULL || getData(node) == NULL)
	{
		return NULL;
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
	else if(diff < 0) // node belongs SOMEWHERE left of tree
	{
		if(tree->left == NULL)
		{
			tree->left = node;
		}
		else
		{
			tree->left = add(tree->left, node, compare, equalAction);
		}
		//tree = balance(tree);
		return tree;
	}
	else if(diff > 0) // node belongs SOMEWHERE right of tree.
	{
		if(tree->right == NULL) // we can just add
		{
			tree->right = node;
		}
		else
		{
			tree->right = add(tree->right, node, compare, equalAction);
		}
		//tree = balance(tree);
		return tree;
	}

	return NULL;
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
	printf("\n");

	if(tree != NULL) // if we have a left child
	{
		printTree(tree->left, level + 1, print);
		printTree(tree->right, level + 1, print);
	}

	return 0;
}
