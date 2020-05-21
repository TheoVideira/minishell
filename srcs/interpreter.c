/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpreter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 17:42:55 by user42            #+#    #+#             */
/*   Updated: 2020/05/15 17:42:55 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		return builtin_exit(args_size(cmd->args), cmd->args, mini);
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


char *search_dir(char *dirname, char *label)
{
	DIR *dir;
	struct dirent *de;
	char **tab;
	int i;

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
	free(dir);
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

int		redir_open_out_append(char **redirs, int i, int foi[2])
{
	int fd;

	if (foi[0] != -1)
		close(foi[0]);
	if ((fd = open(redirs[i] + 2, O_CREAT | O_WRONLY | O_APPEND, 0666)) == -1)
	{
		ft_perror("minishell", redirs[i] + 2, 0);
		return (fd);
	}
	foi[0] = fd;
	dup2(fd, 1);
	return (fd);
}

int		redir_open_out(char **redirs, int i, int foi[2])
{
	int fd;

	if (foi[0] != -1)
		close(foi[0]);
	if ((fd = open(redirs[i] + 1, O_CREAT | O_WRONLY | O_TRUNC, 0666)) == -1)
	{
		ft_perror("minishell", redirs[i] + 1, 0);
		return (fd);
	}
	foi[0] = fd;
	dup2(fd, 1);
	return (fd);
}

int		redir_open_in(char **redirs, int i, int foi[2])
{
	int fd;

	if (foi[1] != -1)
		close(foi[1]);
	if ((fd = open(redirs[i] + 1, O_RDONLY)) == -1)
	{
		ft_perror("minishell", redirs[i] + 1, 0);
		return (fd);
	}
	foi[1] = fd;
	dup2(fd, 0);
	return (fd);
}

int handle_redirs(char **redirs)
{
	int i;
	int fd;
	int foi[2] = { -1, -1 };

	i = 0;
	if (!redirs)
		return (0);
	while (redirs[i])
	{
		if (ft_strncmp(">>", redirs[i], 2) == 0)
			fd = redir_open_out_append(redirs, i, foi);
		else if (ft_strncmp(">", redirs[i], 1) == 0)
			fd = redir_open_out(redirs, i, foi);
		else if (ft_strncmp("<", redirs[i], 1) == 0)
			fd = redir_open_in(redirs, i, foi);
		if (fd == -1)
			break ;
		i++;
	}
	return (fd);
}

void	launch_file(t_cmd *cmd, t_minishell *mini)
{
	struct stat tmp;

	if (stat(cmd->label, &tmp) == -1)
		ft_perror("minishell", "cannot access", cmd->label); // check the right error message
	
	if(tmp.st_mode & S_IEXEC && !S_ISDIR(tmp.st_mode)) 
		execve(cmd->label, cmd->args, mini->envtmp);
	else
	{
		ft_perror(0, "command not found", cmd->label);
		exit(1);	
	}
}


int run_command(t_cmd *cmd, t_minishell *mini)
{
	char *path;	
	int r;
	int fd;

	if ((fd = handle_redirs(cmd->redir)) == -1)
	{
		exit(errno);
	}
	if ((r = execute_builtin(cmd, mini)) > -1)
	{
		// mini->lastcall = r;
		// free all shit
		close(fd);
		exit(r);
	}
	//if file


	if ((ft_strncmp("./", cmd->label, 2) == 0 || ft_strchr(cmd->label, '/')))
		launch_file(cmd, mini);
	

	//if not
	path = find_name(cmd->label, mini);
	execve(path, cmd->args, mini->envtmp); // need to add env trad
	ft_perror("minishell", "command not found", cmd->label);
	printf("%d\n", errno);
	mini->lastcall = 127;
	exit(1);
	return (0);
}

int	format_arr(char **arr, t_minishell *mini)
{
	int i;
	char *tmp;

	i = 0;
	while (arr[i])
	{
		tmp = arr[i];
		arr[i] = format_arg(arr[i], mini);
		free(tmp);
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
	cmd->label = cmd->args[0];
	return (0);
}

int		open_pipe(int i, int io[2], int save[2], t_list *cmd)
{
	if (i > 0)
		dup2(io[0], 0);
	if (cmd->next)
	{
		pipe(io);
		dup2(io[1], 1);
	}
	else
		dup2(save[1], 1);
	return (0);
}

int		close_pipe(int io[2], t_list *cmd)
{
		if (cmd->next)
			close(io[1]);
		return (0);
}

int		launch_processes(t_process *process, int save[2], t_list *cmd, t_minishell *mini)
{
	int i;
	int io[2];

	i = 0;
	while (cmd) 
	{
		open_pipe(i, io, save, cmd);// check error
		if ((process[i].pid = fork()) == 0)
		{
			build_cmd((t_cmd *)cmd->content, mini );// panic
			run_command((t_cmd *)cmd->content, mini); // check if label not found
		}
		else if (process[i].pid == -1)
		{
			// panic
		}
		close_pipe(io, cmd); 
		cmd = cmd->next;
		i++;
	}
	return (0);
}

int		end_processes(t_process *process, int nb, t_minishell *mini)
{
	int i;

	i = -1;
	while (++i < nb)
	{
		waitpid(process[i].pid, &(process[i].status), 0);
		mini->lastcall = WIFEXITED(process[i].pid);
	}
	return (0);
}

int	run_processes(int save[2], int nb, t_list *cmds, t_minishell *mini)
{
	t_process *process;

	if (!(process = ft_calloc(1, sizeof(t_process) * nb)))
		return (-1);
	mini->envtmp = dictoenv(mini->env); // check error and if mini->env == 0
	launch_processes(process, save, cmds, mini); // check error
	end_processes(process, nb, mini); // check error
	dup2(save[0], 0);
	dup2(save[1], 1);
	free(process);
	free_char_array(mini->envtmp);
	return (0);
}

int run_pipeline(t_pipeline *pi, t_minishell *mini)
{
	t_list *l;
	int len;
	int save[2];
	int fd;

	l = pi->cmds;
	len = ft_lstsize(pi->cmds);
	save[0] = dup(0);
	save[1] = dup(1);
	if (len == 1 && is_builtin((t_cmd *)l->content))
	{
		if ((fd = handle_redirs(((t_cmd*)l->content)->redir)) != -1)
		{
			build_cmd((t_cmd *)l->content, mini);// panic
			mini->lastcall = execute_builtin((t_cmd *)l->content, mini); // check if label not found
			close(fd);
		}
		else
			mini->lastcall = 1;
		dup2(save[0], 0);
		dup2(save[1], 1);
		return (mini->lastcall);
	}
	run_processes(save, len, pi->cmds, mini);
	return (mini->lastcall); // value of pipe
}
