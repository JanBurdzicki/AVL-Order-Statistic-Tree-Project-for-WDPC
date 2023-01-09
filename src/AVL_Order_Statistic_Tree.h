#ifndef AVL_ORDER_STATISTIC_TREE_H
#define AVL_ORDER_STATISTIC_TREE_H

#include "Messages_Printing.h"
#include "Libraries_And_Macros.h"

#define AVL_TREE_NULL ((void *) 0)

typedef void *AVL_OS_Tree_Node_Key;
typedef void *AVL_OS_Tree_Node_Value;

typedef int (*AVL_OS_Tree_Compare_Function)(AVL_OS_Tree_Node_Value value_1, AVL_OS_Tree_Node_Value value_2);

struct AVL_OS_Tree_Node
{
	struct AVL_OS_Tree_Node* parent;
	struct AVL_OS_Tree_Node* L;
	struct AVL_OS_Tree_Node* R;

	AVL_OS_Tree_Node_Key key;
	AVL_OS_Tree_Node_Value value;

	int height;
};

typedef struct AVL_OS_Tree_Node AVL_OS_Tree_Node;

struct AVL_OS_Tree
{
	AVL_OS_Tree_Node* root;

	AVL_OS_Tree_Compare_Function compare_function;

	int number_of_nodes;
};

typedef struct AVL_OS_Tree AVL_OS_Tree;

AVL_OS_Tree* avl_os_tree_new(AVL_OS_Tree_Compare_Function compare_function);
void avl_os_tree_free(AVL_OS_Tree* tree);
AVL_OS_Tree_Node* avl_os_tree_insert(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Key key, AVL_OS_Tree_Node_Value value);
void avl_os_tree_remove_node(AVL_OS_Tree* tree, AVL_OS_Tree_Node* node);
bool avl_os_tree_remove(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Key key);
AVL_OS_Tree_Node* avl_os_tree_lookup_node(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Key key);
AVL_OS_Tree_Node_Value avl_os_tree_lookup(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Key key);
AVL_OS_Tree_Node* avl_os_tree_root_node(AVL_OS_Tree* tree);
AVL_OS_Tree_Node_Key avl_os_tree_node_key(AVL_OS_Tree_Node* node);
AVL_OS_Tree_Node_Value avl_os_tree_node_value(AVL_OS_Tree_Node* node);
AVL_OS_Tree_Node* avl_os_tree_node_child(AVL_OS_Tree_Node* node, bool is_left_child);
AVL_OS_Tree_Node* avl_os_tree_node_parent(AVL_OS_Tree_Node* node);
int avl_os_tree_subtree_height(AVL_OS_Tree_Node* node);
int avl_os_tree_number_of_nodes(AVL_OS_Tree* tree);

AVL_OS_Tree_Node* min_element(AVL_OS_Tree* tree);
AVL_OS_Tree_Node* max_element(AVL_OS_Tree* tree);

AVL_OS_Tree_Node* prev(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Value value);
AVL_OS_Tree_Node* next(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Value value);

AVL_OS_Tree_Node_Value* avl_tree_to_array(AVL_OS_Tree *tree);

void print_array(AVL_OS_Tree* tree);
void print_tree(AVL_OS_Tree* tree);

#endif