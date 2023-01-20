#include "AVL_Order_Statistic_Tree.h"

AVL_OS_Tree_Node_Value values[MAX_N][MAX_DEPTH];
int value_index[MAX_DEPTH];

AVL_OS_Tree* avl_os_tree_new(AVL_OS_Tree_Compare_Function compare_function)
{
	AVL_OS_Tree* tree = NULL;

	tree = (AVL_OS_Tree*) malloc(sizeof(AVL_OS_Tree));

	if(tree == NULL)
	{
		print_error(stderr, "", "\n-----------------------------------\n");
		print_error(stderr, "ERROR", "Blad alokacji pamieci za pomoca funkcji malloc()!\n");
		print_error(stderr, "", "-----------------------------------\n\n");

		exit(EXIT_FAILURE);
	}

	tree->root = NULL;
	tree->compare_function = compare_function;
	tree->number_of_nodes = 0;

	return tree;
}

static void avl_os_tree_free_subtree(AVL_OS_Tree* tree, AVL_OS_Tree_Node* node)
{
	if(node == NULL)
	{
		return;
	}

	avl_os_tree_free_subtree(tree, node->L);
	avl_os_tree_free_subtree(tree, node->R);

	free(node);
}

void avl_os_tree_free(AVL_OS_Tree* tree)
{
	avl_os_tree_free_subtree(tree, tree->root);

	free(tree);
}

int avl_os_tree_subtree_height(AVL_OS_Tree_Node* node)
{
	if(node == NULL)
	{
		return 0;
	}

	else
	{
		return node->height;
	}
}

int max(int a, int b)
{
	return (a > b) ? a : b;
}

static void avl_os_tree_update_height(AVL_OS_Tree_Node* node)
{
	AVL_OS_Tree_Node* subtree_L = node->L;
	AVL_OS_Tree_Node* subtree_R = node->R;

	int height_L = avl_os_tree_subtree_height(subtree_L);
	int height_R = avl_os_tree_subtree_height(subtree_R);

	node->height = max(height_L, height_R) + 1;
}

static bool is_left_side_child(AVL_OS_Tree_Node* node)
{
	return (node->parent->L == node);
}

static void avl_os_tree_node_replace(AVL_OS_Tree* tree, AVL_OS_Tree_Node* node_1, AVL_OS_Tree_Node* node_2)
{
	if(node_2 != NULL)
	{
		node_2->parent = node_1->parent;
	}

	if(node_1->parent == NULL)
	{
		tree->root = node_2;
	}

	else
	{
		if(is_left_side_child(node_1))
		{
			node_1->parent->L = node_2;
		}

		else
		{
			node_1->parent->R = node_2;
		}

		avl_os_tree_update_height(node_1->parent);
	}
}

static AVL_OS_Tree_Node* avl_os_tree_rotate(AVL_OS_Tree* tree, AVL_OS_Tree_Node* node, bool is_left_rotation)
{
	AVL_OS_Tree_Node* root;

	if(is_left_rotation)
	{
		root = node->R;
	}

	else
	{
		root = node->L;
	}

	avl_os_tree_node_replace(tree, node, root);

	if(is_left_rotation)
	{
		node->R = root->L;

		root->L = node;
	}

	else
	{
		node->L = root->R;

		root->R = node;
	}

	node->parent = root;

	if(is_left_rotation)
	{
		if(node->R != NULL)
		{
			node->R->parent = node;
		}
	}

	else
	{
		if(node->L != NULL)
		{
			node->L->parent = node;
		}
	}

	avl_os_tree_update_height(root);
	avl_os_tree_update_height(node);

	return root;
}

static AVL_OS_Tree_Node* avl_os_tree_node_balance(AVL_OS_Tree* tree, AVL_OS_Tree_Node* node)
{
	AVL_OS_Tree_Node* subtree_L = node->L;
	AVL_OS_Tree_Node* subtree_R = node->R;
	AVL_OS_Tree_Node* child;

	int height_L = avl_os_tree_subtree_height(subtree_L);
	int height_R = avl_os_tree_subtree_height(subtree_R);

	int difference = height_R - height_L;

	if(difference >= 2)
	{
		child = subtree_R;

		if(avl_os_tree_subtree_height(child->R) < avl_os_tree_subtree_height(child->L))
		{
			avl_os_tree_rotate(tree, subtree_R, false);
		}

		node = avl_os_tree_rotate(tree, node, true);
	}

	else
	{
		if(difference <= -2)
		{
			child = subtree_L;

			if(avl_os_tree_subtree_height(child->L) < avl_os_tree_subtree_height(child->R))
			{
				avl_os_tree_rotate(tree, subtree_L, true);
			}

			node = avl_os_tree_rotate(tree, node, false);
		}
	}

	avl_os_tree_update_height(node);

	return node;
}

static void avl_os_tree_balance_to_root(AVL_OS_Tree* tree, AVL_OS_Tree_Node* node)
{
	AVL_OS_Tree_Node* node_balance = node;

	while(node_balance != NULL)
	{
		node_balance = avl_os_tree_node_balance(tree, node_balance);

		node_balance = node_balance->parent;
	}
}

AVL_OS_Tree_Node* avl_os_tree_node_new(AVL_OS_Tree_Node* parent, AVL_OS_Tree_Node_Key key, AVL_OS_Tree_Node_Value value)
{
	AVL_OS_Tree_Node* node = NULL;

	node = (AVL_OS_Tree_Node*) malloc(sizeof(AVL_OS_Tree_Node));

	if(node == NULL)
	{
		print_error(stderr, "", "\n-----------------------------------\n");
		print_error(stderr, "ERROR", "Blad alokacji pamieci za pomoca funkcji malloc()!\n");
		print_error(stderr, "", "-----------------------------------\n\n");

		exit(EXIT_FAILURE);
	}

	node->L = NULL;
	node->R = NULL;
	node->parent = parent;
	node->key = key;
	node->value = value;
	node->height = 1;

	return node;
}

AVL_OS_Tree_Node* avl_os_tree_insert(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Key key, AVL_OS_Tree_Node_Value value)
{
	AVL_OS_Tree_Node** node_balance = &tree->root;
	AVL_OS_Tree_Node* previous_node = NULL;

	while(*node_balance != NULL)
	{
		previous_node = *node_balance;

		if(tree->compare_function(key, (*node_balance)->key) < 0)
		{
			node_balance = &((*node_balance)->L);

		}

		else
		{
			node_balance = &((*node_balance)->R);
		}
	}

	AVL_OS_Tree_Node* new_node = avl_os_tree_node_new(previous_node, key, value);

	*node_balance = new_node;

	avl_os_tree_balance_to_root(tree, previous_node);

	tree->number_of_nodes++;

	return new_node;
}

static AVL_OS_Tree_Node* avl_os_tree_node_get_replacement(AVL_OS_Tree *tree, AVL_OS_Tree_Node *node)
{
	AVL_OS_Tree_Node* subtree_L = node->L;
	AVL_OS_Tree_Node* subtree_R = node->R;
	AVL_OS_Tree_Node* result;
	AVL_OS_Tree_Node* child;

	if(subtree_L == NULL && subtree_R == NULL)
	{
		return NULL;
	}

	int height_L = avl_os_tree_subtree_height(subtree_L);
	int height_R = avl_os_tree_subtree_height(subtree_R);

	if(height_L < height_R)
	{
		result = node->R;

		while(result->L != NULL)
		{
			result = result->L;
		}

		child = result->R;
	}

	else
	{
		result = node->L;

		while(result->R != NULL)
		{
			result = result->R;
		}

		child = result->L;
	}

	avl_os_tree_node_replace(tree, result, child);

	avl_os_tree_update_height(result->parent);

	return result;
}

void avl_os_tree_remove_node(AVL_OS_Tree *tree, AVL_OS_Tree_Node *node)
{
	AVL_OS_Tree_Node* swap_node;
	AVL_OS_Tree_Node* balance_startpoint;

	swap_node = avl_os_tree_node_get_replacement(tree, node);

	if(swap_node == NULL)
	{
		avl_os_tree_node_replace(tree, node, NULL);

		balance_startpoint = node->parent;

	}

	else
	{
		if(swap_node->parent == node)
		{
			balance_startpoint = swap_node;
		}

		else
		{
			balance_startpoint = swap_node->parent;
		}

		swap_node->L = node->L;
		swap_node->R = node->R;

		if(swap_node->L != NULL)
		{
			swap_node->L->parent = swap_node;
		}

		if(swap_node->R != NULL)
		{
			swap_node->R->parent = swap_node;
		}

		swap_node->height = node->height;

		avl_os_tree_node_replace(tree, node, swap_node);
	}

	free(node);

	tree->number_of_nodes--;

	avl_os_tree_balance_to_root(tree, balance_startpoint);
}

bool avl_os_tree_remove(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Key key)
{
	AVL_OS_Tree_Node* node;

	node = avl_os_tree_lookup_node(tree, key);

	if(tree->compare_function(avl_os_tree_node_key(node), key) == 0)
	{
		avl_os_tree_remove_node(tree, node);

		return EXIT_SUCCESS;
	}

	else
	{
		return EXIT_FAILURE;
	}
}

AVL_OS_Tree_Node* avl_os_tree_lookup_node(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Key key)
{
	AVL_OS_Tree_Node* node;

	int difference;

	node = tree->root;

	while(node != NULL)
	{
		difference = tree->compare_function(key, node->key);

		if(difference == 0)
		{
			break;
		}

		else
		{
			if(difference < 0)
			{
				node = node->L;
			}

			else
			{
				node = node->R;
			}
		}
	}

	return node;
}

AVL_OS_Tree_Node_Value avl_os_tree_lookup(AVL_OS_Tree *tree, AVL_OS_Tree_Node_Key key)
{
	AVL_OS_Tree_Node* node;

	node = avl_os_tree_lookup_node(tree, key);

	if(avl_os_tree_node_key(node) == key)
	{
		return node->value;
	}

	else
	{
		return AVL_TREE_NULL;
	}
}

AVL_OS_Tree_Node* avl_os_tree_root_node(AVL_OS_Tree* tree)
{
	return tree->root;
}

AVL_OS_Tree_Node_Key avl_os_tree_node_key(AVL_OS_Tree_Node *node)
{
	return node->key;
}

AVL_OS_Tree_Node_Value avl_os_tree_node_value(AVL_OS_Tree_Node *node)
{
	return node->value;
}

AVL_OS_Tree_Node *avl_os_tree_node_child(AVL_OS_Tree_Node *node, bool is_left_child)
{
	if(is_left_child)
	{
		return node->L;
	}

	else
	{
		return node->R;
	}
}

AVL_OS_Tree_Node *avl_os_tree_node_parent(AVL_OS_Tree_Node *node)
{
	return node->parent;
}

int avl_os_tree_number_of_nodes(AVL_OS_Tree *tree)
{
	return tree->number_of_nodes;
}

AVL_OS_Tree_Node* min_element(AVL_OS_Tree* tree)
{
	AVL_OS_Tree_Node* node = tree->root;

	if(node == NULL)
	{
		return NULL;
	}

	while(node->L != NULL)
	{
		node = node->L;
	}

	return node;
}

AVL_OS_Tree_Node* max_element(AVL_OS_Tree* tree)
{
	AVL_OS_Tree_Node* node = tree->root;

	if(node == NULL)
	{
		return NULL;
	}

	while(node->R != NULL)
	{
		node = node->R;
	}

	return node;
}

static void avl_tree_to_array_add_subtree(AVL_OS_Tree_Node* subtree, AVL_OS_Tree_Node_Value* array, int* index)
{
	if(subtree == NULL)
	{
		return;
	}

	avl_tree_to_array_add_subtree(subtree->L, array, index);

	array[*index] = subtree->value;

	(*index)++;

	avl_tree_to_array_add_subtree(subtree->R, array, index);
}

AVL_OS_Tree_Node_Value* avl_tree_to_array(AVL_OS_Tree* tree)
{
	AVL_OS_Tree_Node_Value* array = (AVL_OS_Tree_Node_Value*) malloc(tree->number_of_nodes * sizeof(AVL_OS_Tree_Node_Value));

	if(array == NULL)
	{
		return NULL;
	}

	int index = 0;

	avl_tree_to_array_add_subtree(tree->root, array, &index);

	return array;
}

static void find_predecessor_and_successor(AVL_OS_Tree* tree, AVL_OS_Tree_Node** predecessor, AVL_OS_Tree_Node** successor, AVL_OS_Tree_Node_Key key)
{
	AVL_OS_Tree_Node* node = tree->root;

	int difference;

	while(node != NULL)
	{
		difference = tree->compare_function(node->key, key);

		if(difference == 0)
		{
			if(node->L != NULL)
			{
				(*predecessor) = node->L;

				while((*predecessor)->R != NULL)
				{
					(*predecessor) = (*predecessor)->R;
				}
			}

			if(node->R != NULL)
			{
				(*successor) = node->R;

				while((*successor)->L != NULL)
				{
					(*successor) = (*successor)->L;
				}
			}

			return;
		}

		else
		{
			if(difference < 0)
			{
				(*predecessor) = node;

				node = node->R;
			}

			else
			{
				(*successor) = node;

				node = node->L;
			}
		}
	}
}

AVL_OS_Tree_Node* prev(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Value value)
{
	AVL_OS_Tree_Node* predecessor = NULL;
	AVL_OS_Tree_Node* successor = NULL;

	find_predecessor_and_successor(tree, &predecessor, &successor, value);

	return predecessor;
}

AVL_OS_Tree_Node* next(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Value value)
{
	AVL_OS_Tree_Node* predecessor = NULL;
	AVL_OS_Tree_Node* successor = NULL;

	find_predecessor_and_successor(tree, &predecessor, &successor, value);

	return successor;
}

void DFS(AVL_OS_Tree_Node* node, int depth)
{
	if(node != NULL)
	{
		int* value = (int*) avl_os_tree_node_value(node);

		DFS(node->L, depth + 1);
		DFS(node->R, depth + 1);

		values[value_index[depth]][depth] = node->value;
		value_index[depth]++;
	}

	else
	{
		value_index[depth]++;
	}
}

void print_array(AVL_OS_Tree* tree)
{
	int** array = (int**) avl_tree_to_array(tree);

	int size = tree->number_of_nodes;

	FOR(i, size)
	{
		printf("%d ", *array[i]);
	}

	printf("\n");

	free(array);
}

void print_tree(AVL_OS_Tree* tree)
{
	DFS(tree->root, 0);

	FOR(i, (1 << MAX_DEPTH))
	{
		FOR(j, MAX_DEPTH)
		{
			int* value = (int*) values[i][j];

			if(j <= (int) log2(i) || value == NULL)
			{
				printf("%10s\t", "");
			}

			else
			{
				printf("%10d\t", *value);
			}
		}

		printf("\n");
	}

	FOR(i, MAX_DEPTH)
	{
		value_index[i] = 0;
	}

	FOR(i, (1 << MAX_DEPTH))
	{
		FOR(j, MAX_DEPTH)
		{
			values[i][j] = NULL;
		}
	}
}