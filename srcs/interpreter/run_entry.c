#include <minishell.h>

int run_entry(t_entry *entry)
{
	t_list *tree;
	int r;

	tree = entry->instructions;
	r = 0;
	while (tree)
	{
		r = run_tree((t_node *)tree->content);
		if (r == ALLOC_ERROR)
			alloc_error();
		else if (r == FATAL_ERROR)
			fatal_error();
		tree = tree->next;
	}
	return (0);
}
