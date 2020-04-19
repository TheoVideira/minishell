
#include <minishell.h>

int		run_entry(t_entry *entry)
{
	t_list *tree;
	int r;

	tree = entry->instructions;
	while (tree)
	{
		r = run_tree((t_node*)tree->content);
		tree = tree->next;
	}
	return (r); // check what's right to do here
}

int		run_tree(t_node *tree)
{
	if (tree->type == PIPELINE)
		return (run_pipeline(tree->pipeline));
	if (tree->type == OR)
		return (run_tree(tree->left) || run_tree(tree->right));
	if (tree->type == AND)
		return (run_tree(tree->left) && run_tree(tree->right));
	return (0);
}

int		is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (1);
	if (!ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "export"))
		return (1);
	if (!ft_strcmp(str, "unset"))
		return (1);
	if (!ft_strcmp(str, "env"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

int		run_command(t_cmd *cmd)
{
	char **av;
	int ac;


	// int fd[2];

	// if (!cmds)
	// 	return (0);
	
	// if (pipe(fd))
	// 	return (1);
	if (ft_strcmp(cmd->label, "echo") == 0)
	{
		av = list_to_char_array(cmd->args); // check error
		ac = ft_lstsize(cmd->args);
		return echo(ac, av);
	}
	return (0);
}

int		run_pipeline(t_pipeline *pipe)
{
	t_list *l;
	t_cmd* c;

	//FORK CHARABIA
	l = pipe->cmds;
	c = (t_cmd*)l->content;
	//Pour chaque commande
	return run_command(c);
}