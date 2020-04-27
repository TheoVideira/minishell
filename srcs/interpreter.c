
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
	return (r); // check what's right to do here
}

int run_tree(t_node *tree, t_minishell *mini)
{
	if (tree->type == PIPELINE)
		return (run_pipeline(tree->pipeline, mini));
	if (tree->type == OR)
		return (!(run_tree(tree->left, mini) == 0 || run_tree(tree->right, mini) == 0));
	if (tree->type == AND)
		return (!(run_tree(tree->left, mini) == 0 && run_tree(tree->right, mini) == 0));
	return (0);
}

int		args_size(char **args)
{
	int i;

	i = 0;
	while (args[i])
	{
		i++;
	}
	return (i);
}

int		execute_builtin(t_cmd* cmd, t_minishell *mini)
{
	if (!ft_strcmp(cmd->label, "echo"))
		return (builtin_echo(args_size(cmd->args), cmd->args));
	if (!ft_strcmp(cmd->label, "cd"))
		return (builtin_cd(args_size(cmd->args), cmd->args, mini->env));
	if (!ft_strcmp(cmd->label, "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(cmd->label, "export"))
		return builtin_export(args_size(cmd->args), cmd->args, mini->env);
	if (!ft_strcmp(cmd->label, "unset"))
		return builtin_unset(args_size(cmd->args), cmd->args, mini->env);
	if (!ft_strcmp(cmd->label, "env"))
		return builtin_env(mini->env);
	if (!ft_strcmp(cmd->label, "exit"))
		return builtin_exit(args_size(cmd->args), cmd->args);
	return (-1);
}

int		is_builtin(t_cmd* cmd)
{
	if (!ft_strcmp(cmd->label, "echo"))
		return (1);
	if (!ft_strcmp(cmd->label, "cd"))
		return (1);
	if (!ft_strcmp(cmd->label, "pwd"))
		return (1);
	if (!ft_strcmp(cmd->label, "export"))
		return (1);
	if (!ft_strcmp(cmd->label, "unset"))
		return (1);
	if (!ft_strcmp(cmd->label, "env"))
		return (1);
	if (!ft_strcmp(cmd->label, "exit"))
		return (1);
	return (0);
}

// WHY it works ?
void free_char_array(char **arr)
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
	(void)label;

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

char *compute_full_path(char *dirname, char *bin)
{
	size_t lendir;
	size_t lenbin;
	unsigned int slash;
	char *fullname;

	lendir = ft_strlen(dirname);
	lenbin = +ft_strlen(bin);
	slash = dirname[lendir - 1] == '/';
	if (!(fullname = ft_calloc(1, sizeof(char) * (lendir + lenbin + !slash + 1))))
		return (0);
	ft_strlcpy(fullname, dirname, lendir + 1);
	if (!slash)
		fullname[lendir] = '/';
	ft_strlcpy(fullname + lendir + !slash, bin, lenbin + 1);
	return (fullname);
}

char *find_name(char *label, t_minishell *mini)
{
	char *path;
	char **entries;
	char *name;
	char *r;
	int i;

	name = 0;
	path = (char *)ft_dictget(mini->env, "PATH");
	if (!(entries = ft_split(path, ':')))
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

int run_command(t_cmd *cmd, t_minishell *mini)
{
	char *path;
	struct stat tmp;
	int r;

	if ((r = execute_builtin(cmd, mini)) > -1)
	{
		mini->lastcall = r;
		// free all shit
		exit(r);
	}
	if ((ft_strncmp("./", cmd->label, 2) == 0 || ft_strchr(cmd->label, '/')) && stat(cmd->label, &tmp) >= 0 && tmp.st_mode & S_IEXEC && !S_ISDIR(tmp.st_mode))
		execve(cmd->label, cmd->args, mini->envtmp); // need to add env tradd
	path = find_name(cmd->label, mini);
	printf("chemin trouve for \"%s\": %s\n", cmd->label, path);
	execve(path, cmd->args, mini->envtmp); // need to add env tradd
	return (0);
}

// int init_process_arr(t_process *process)
// {
// 	int len;

// 	len = ft_lstsize(l);
// 	if (!(*pid = ft_calloc(sizeof(pid_t) * len)))
// 		return (1);
// 	if (!(*status = ft_calloc(sizeof(int) * len)))
// 	{
// 		free(*pid);
// 		return (1);
// 	}	
// 	return (0);
// }


// int		format_args(char **arr)
// {
// 	while (/* condition */)
// 	{
// 		/* code */
// 	}
	
// }

// int		format_redir(char **redir)
// {
	
// }

// int		format_input(char **redir)
// {
	
// }


int	format_arr(char **arr, t_minishell *mini)
{
	int i;

	i = 0;
	while (arr[i])
	{
		arr[i] = format_arg(arr[i], mini);
		if (arr[i] == 0)
			return (2); // panic
		i++;
	}
	return (0);
}


int	build_cmd(t_cmd	*cmd, t_minishell *mini)
{
	if (cmd->args && format_arr(cmd->args, mini))
		return (1);
	if (cmd->redir && format_arr(cmd->redir, mini))
		return (1);
	if (cmd->input && format_arr(cmd->input, mini))
		return (1);
	return (0);
}


int run_pipeline(t_pipeline *pi, t_minishell *mini)
{
	t_list *l;
	t_process *process;
	int i;
	int len;
	int save[2];
	int io[2];

	l = pi->cmds;
	len = ft_lstsize(pi->cmds);
	if (len == 1 && is_builtin((t_cmd *)l->content))
	{
		build_cmd((t_cmd *)l->content, mini);// panic
		mini->lastcall = execute_builtin((t_cmd *)l->content, mini); // check if label not found
		return (mini->lastcall);
	}
	save[0] = dup(0);
	save[1] = dup(1);
	i = 0;
	if (!(process = ft_calloc(1, sizeof(t_process)* ft_lstsize(pi->cmds))))
		return (0);	
	mini->envtmp = dictoenv(mini->env); // check error

	while (i < len)
	{
		if (i > 0)
		{	
			dup2(io[0], 0);
		}
		if (l->next)
		{
			pipe(io);
			dup2(io[1], 1);
		}
		else
		{	
			dup2(save[1], 1);
		}
		
		if ((process[i].pid = fork()) == 0)
		{
			build_cmd((t_cmd *)l->content, mini);// panic
			run_command((t_cmd *)l->content, mini); // check if label not found
		}
		else if (process[i].pid == -1)
		{
			//panic
		}
		if (i > 1)
			close(io[0]);
		if (l->next)
			close(io[1]);
		
		l = l->next;
		i++;
	}
	i = 0;
	while (i < len)
	{
		waitpid(process[i].pid, &(process[i].status), 0);
		mini->lastcall = process[i].status;
		i++;
	}
	dup2(save[0], 0);
	dup2(save[1], 1);
	free(process);
	return (mini->lastcall); // value of pipe
}
