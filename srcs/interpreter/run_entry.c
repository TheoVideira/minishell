#include <minishell.h>

int run_entry(t_entry *entry, t_minishell *mini)
{
	t_list *tree;
	int r;

	tree = entry->instructions;
	r = 0;
	while (tree)
	{
		r = run_tree((t_node *)tree->content, mini);
		if (!r)
			return (r);
		tree = tree->next;
	}
	return (r);
}
