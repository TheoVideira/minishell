
#include <minishell.h>

int		run_tree(t_node *tree)
{
	if (tree->type == PIPELINE)
		return (run_pipeline(tree->pipeline));
	if (tree->type == OR)
		return (run_tree(tree->left) || run_tree(tree->right));
	if (tree->type == AND)
		return (run_tree(tree->left) && run_tree(tree->right));
}