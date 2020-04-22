
#include <minishell.h>

int		run_entry(t_entry *entry, t_minishell *mini)
{
	t_list *tree;
	int r;

	tree = entry->instructions;
	while (tree)
	{
		r = run_tree((t_node*)tree->content, mini);
		tree = tree->next;
	}
	return (r); // check what's right to do here
}

int		run_tree(t_node *tree, t_minishell *mini)
{
	if (tree->type == PIPELINE)
		return (run_pipeline(tree->pipeline, mini));
	if (tree->type == OR)
		return (run_tree(tree->left, mini) || run_tree(tree->right, mini));
	if (tree->type == AND)
		return (run_tree(tree->left, mini) && run_tree(tree->right, mini));
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



// WHY it works ?
void	free_char_array(char **arr)
{
	char **ptr;

	ptr = arr;
	while (*ptr)
	{
		free(*ptr);
		ptr++;
	}
	free(arr);
}

char *search_dir(char *dirname, char *label)
{
	DIR *dir;
	struct dirent *de;
	char **tab;
	int i;
	(void) label;

	if (!(dir = opendir(dirname)))
	{
		//could not open directory
		return (0);
	}
	while ((de = readdir(dir)))
	{
		i = 0;
		tab = ft_split(de->d_name, '/');
		while (tab[i])
		{
			if (ft_strcmp(label, tab[i]) == 0)
			{
				free_char_array(tab);
				return (de->d_name);
			}
			i++;
		}
		free_char_array(tab);
	}
	return (0);

}

char	*compute_full_path(char *dirname, char *bin)
{
	size_t lendir;
	size_t lenbin;
	unsigned int slash;
	char *fullname;

	lendir = ft_strlen(dirname);
	lenbin =  + ft_strlen(bin);
	slash = dirname[lendir - 1] == '/';
	if (!(fullname = ft_calloc(1, sizeof(char)*(lendir + lenbin + !slash + 1))))
		return (0);
	ft_strlcpy(fullname, dirname, lendir + 1);
	if (!slash)
		fullname[lendir] = '/';
	ft_strlcpy(fullname + lendir + !slash, bin, lenbin + 1);
	return (fullname);
}

char	*find_name(char *label, t_minishell *mini)
{
	char *path;
	char **entries;
	char *name;
	char *r;
	int i;

	name = 0;
	path = ft_dictget(mini->env, "PATH");
	if(!(entries = ft_split(path, ':')))
	{
		// panic
		return (0);
	}
	i = 0;
	while (entries[i])
	{
		if ((name = search_dir(entries[i], label)))
		{
			if (!(r = compute_full_path(entries[i], name)))
			{
				// panic
				return (0);
			}
			free_char_array(entries);
			return (r);
		}
		i++;
	}
	free_char_array(entries);
	return (0);
}

int		run_command(t_cmd *cmd, t_minishell *mini)
{
	char **av;
	int ac;
	int fd[2];


	if (pipe(fd))
		return (1);

	printf("chemin trouve: %s\n", find_name(cmd->label, mini));

	// if (!cmds)
	// 	return (0);


	if (ft_strcmp(cmd->label, "echo") == 0)
	{
		av = list_to_char_array(cmd->args); // check error
		ac = ft_lstsize(cmd->args);
		return echo(ac, av);
	}
	return (0);
}

int		run_pipeline(t_pipeline *pipe, t_minishell *mini)
{
	t_list *l;
	t_cmd* c;

	//FORK CHARABIA
	l = pipe->cmds;
	c = (t_cmd*)l->content;
	//Pour chaque commande
	return run_command(c, mini);
}