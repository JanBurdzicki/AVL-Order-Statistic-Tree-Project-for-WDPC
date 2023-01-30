# Documentation

## AVL_Order_Statistic_Tree

* `AVL_OS_Tree_Node_Key` - void pointer (`void*`)
* `AVL_OS_Tree_Node_Value` - void pointer (`void*`)
* `int (*AVL_OS_Tree_Compare_Function)(AVL_OS_Tree_Node_Value value_1, AVL_OS_Tree_Node_Value value_2)` - a function that compares 2 values in the tree (returns negative number if `value_1` < `value_2`, positive number if `value_1` > `value_2`, 0 if `value_1` == `value_2`)
* **struct AVL_OS_Tree_Node** - node in the AVL Order Statistic Tree:
	* **attributes**:
		* `AVL_OS_Tree_Node* parent` - parent of the node
		* `AVL_OS_Tree_Node* L` - left child of the node
		* `AVL_OS_Tree_Node* R` - right child of the node
		* `AVL_OS_Tree_Node_Key key` - key in the node
		* `AVL_OS_Tree_Node_Value value` - value in the node
		* `int height` - height of the subtree of the node
* **struct AVL_OS_Tree** - AVL Order Statistic Tree:
	* **attributes**:
		* `AVL_OS_Tree_Node* root` - root node of the tree
		* `AVL_OS_Tree_Compare_Function compare_function` - a function that compares 2 values in the tree
		* `int number_of_nodes` - number of nodes in the tree

* **Methods**:
* `AVL_OS_Tree* avl_os_tree_new(AVL_OS_Tree_Compare_Function compare_function)` - creates a new AVL Order Statistic Tree (returns a new tree or `NULL` if it was not possible to allocate the new memory)
* `void avl_os_tree_free(AVL_OS_Tree* tree)` - frees the memory allocated to the `tree`
* `AVL_OS_Tree_Node* avl_os_tree_insert(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Key key, AVL_OS_Tree_Node_Value value)` - inserts a new key-value pair into the `tree` (returns the newly created tree node containing the key and value or `NULL` if it was not possible to allocate the new memory)
* `void avl_os_tree_remove_node(AVL_OS_Tree* tree, AVL_OS_Tree_Node* node)` - removes the `node` from the `tree`
* `bool avl_os_tree_remove(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Key key)` - removes a node with the given `key` from the `tree` (returns `false` if no node with the given `key` was found in the tree, `true` if a node with the given `key` was removed)
* `AVL_OS_Tree_Node* avl_os_tree_lookup_node(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Key key)` - searches `tree` for a node with the given `key` (returns the tree node containing the given `key` or `NULL` if no node with the given `key` was found)
* `AVL_OS_Tree_Node_Value avl_os_tree_lookup(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Key key)` - searches `tree` for a value corresponding to the given `key` (returns the value corresponding to the given `key` or `AVL_TREE_NULL` if no node with the given `key` was found)
* `AVL_OS_Tree_Node* avl_os_tree_root_node(AVL_OS_Tree* tree)` - searches `tree` for a root node (returns root node of the `tree` or `NULL` if the `tree` is empty)
* `AVL_OS_Tree_Node_Key avl_os_tree_node_key(AVL_OS_Tree_Node* node)` - returns the key corresponding to the given `node`
* `AVL_OS_Tree_Node_Value avl_os_tree_node_value(AVL_OS_Tree_Node* node)` - returns the value corresponding to the given `node`
* `AVL_OS_Tree_Node* avl_os_tree_node_child(AVL_OS_Tree_Node* node, bool is_left_child)` - returns the child of the `node` or `NULL` if the `node` has no child on the given side
* `AVL_OS_Tree_Node* avl_os_tree_node_parent(AVL_OS_Tree_Node* node)` - returns the parent node of the `node` or `NULL` if `node` is the root node
* `int avl_os_tree_subtree_height(AVL_OS_Tree_Node* node)` - finds the height of the subtree of the `node`
* `int avl_os_tree_number_of_nodes(AVL_OS_Tree* tree)` - returns number of nodes in the `tree`

* `AVL_OS_Tree_Node* min_element(AVL_OS_Tree* tree)` - returns min element in the `tree` or `NULL` if the `tree` is empty
* `AVL_OS_Tree_Node* max_element(AVL_OS_Tree* tree)` - returns max element in the `tree` or `NULL` if the `tree` is empty

* `AVL_OS_Tree_Node* prev(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Value value)` - returns predecessor of the `value` in the `tree`
* `AVL_OS_Tree_Node* next(AVL_OS_Tree* tree, AVL_OS_Tree_Node_Value value)` - returns successor of the `value` in the `tree`

* `AVL_OS_Tree_Node_Value* avl_tree_to_array(AVL_OS_Tree *tree)` - returns a sorted array of values in the `tree`

* `void print_array(AVL_OS_Tree* tree)` - prints a sorted array of values in the `tree`
* `void print_tree(AVL_OS_Tree* tree)` - prints `tree`

## Messages_Printing

* `bool is_string_empty(char* message)` - checks if the `message` is empty
* `void change_color(FILE* stream, char* color)` - changes the color of the output on the `stream` to `color`
* `void set_default_color(FILE* stream)` - sets the color of the output to default on the `stream`
* `void print_message(FILE* stream, char* tag, char* message, char* tag_color, char* message_color)` - prints tag and message on the `stream` where `tag` is in the `tag_color` color and `message` is in the `message_color` color
* `void print_error(FILE* stream, char* tag, char* message)` - prints tag and message on the `stream` where `tag` is in the `BOLD_RED_COLOR` color and `message` is in the `RED_COLOR` color
* `void print_text(FILE* stream, char* tag, char* message)` - prints message on the `stream` where `tag` is in the `BOLD_CYAN_COLOR` color and `message` is in the `DEFAULT_COLOR` color
* `void color_messages_printing_test()` - prints a set of test messages with different colors

## Input Handling

* `void print_operations()` - prints possible queries
* `void read_data(AVL_OS_Tree* tree)` - reads user queries