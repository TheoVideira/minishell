#include <minishell.h>

int run_tree(t_node *tree, t_minishell *mini)
{
	int r1;
	int r2;

	if (tree->type == PIPELINE)
		return (run_pipeline(tree->pipeline, mini));
	if (tree->type == OR)
	{
		r1 = run_tree(tree->left, mini);
		r2 = run_tree(tree->right, mini);
		return (!(r1 == 0 || r2 == 0));
	}
	if (tree->type == AND)
		return (!(run_tree(tree->left, mini) == 0 && run_tree(tree->right, mini) == 0));
	return (0);
}