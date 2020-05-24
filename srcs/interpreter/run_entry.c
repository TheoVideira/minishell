#include <minishell.h>

int run_entry(t_entry *entry, t_minishell *mini)
{
	t_list *tree;
	int r;

	tree = entry->instructions;
	while (tree)
	{
		r = run_tree((t_node *)tree->content, mini);
		tree = tree->next;
	}
	return (r);
}
