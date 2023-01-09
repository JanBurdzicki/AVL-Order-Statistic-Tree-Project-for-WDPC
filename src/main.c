#include "Messages_Printing.h"
#include "Input_Handling.h"
#include "AVL_Order_Statistic_Tree.h"
#include "Libraries_And_Macros.h"

int compare_function(void* _a, void* _b)
{
	int a = *(int*) _a;
	int b = *(int*) _b;

	return (a - b);
}

int main()
{
	// color_messages_printing_test();

	AVL_OS_Tree* tree = avl_os_tree_new((AVL_OS_Tree_Compare_Function) compare_function);

	read_data(tree);

	avl_os_tree_free(tree);

	return 0;
}