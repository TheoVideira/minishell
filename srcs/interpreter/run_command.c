/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:07:17 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 03:35:44 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void		command_not_found(char *label)
{
	char *str1;

	if ((str1 = ft_strjoin(label, " : command not found\n")) == 0)
	{
		alloc_error();
		exit(1);
	}
	ft_putstr_fd(str1, 2);
	free(str1);
}

static int	search_entry(char *entry, char *label, char **ex)
{
	struct stat	tmp;

	if (stat(entry, &tmp) == -1)
		return (0);
	if (S_ISDIR(tmp.st_mode))
		return (search_dir(entry, label, ex));
	return (0);
}

static int	find_name(char *label, char **ex)
{
	char	*path;
	char	**entries;
	int		i;
	int		r;

	*ex = 0;
	if (((path = (char *)ft_dictget(g_mini.env, "PATH")) == 0
			|| ft_strlen(path) == 0) && (path = getcwd(NULL, 0)) == 0)
	{
		fatal_error("getcwd");
		exit(1);
	}
	if (!(entries = ft_split(path, ':')))
		return (ALLOC_ERROR);
	i = -1;
	while (entries[++i])
	{
		if ((r = search_entry(entries[i], label, ex)) < 0)
			free_char_array(entries);
		if (r)
			return (r);
	}
	free_char_array(entries);
	free(path);
	return (0);
}

static void	launch_file(t_cmd *cmd)
{
	struct stat tmp;

	if (stat(cmd->label, &tmp) == -1)
	{
		fatal_error(cmd->label);
		exit(127);
	}
	if (S_ISDIR(tmp.st_mode))
	{
		errno = EISDIR;
		fatal_error(cmd->label);
		exit(126);
	}
	if ((tmp.st_mode & S_IEXEC) == 0)
	{
		errno = EACCES;
		fatal_error(cmd->label);
		exit(126);
	}
	execve(cmd->label, cmd->args, g_mini.envtmp);
	fatal_error(cmd->label);
	exit(1);
}

int			run_command(t_cmd *cmd)
{
	char	*path;
	int		r;
	int		fd;

	if ((fd = handle_redirs(cmd->redir)) == FATAL_ERROR)
		return (FATAL_ERROR);
	r = 0;
	if ((cmd->label == 0) || (r = execute_builtin(cmd)) > -1)
	{
		close(fd);
		exit(r);
	}
	if ((ft_strncmp("./", cmd->label, 2) == 0 || ft_strchr(cmd->label, '/')))
		launch_file(cmd);
	if ((r = find_name(cmd->label, &path)) < 0)
		return (r);
	if (r == 0)
	{
		command_not_found(cmd->label);
		exit(127);
	}
	execve(path, cmd->args, g_mini.envtmp);
	fatal_error(cmd->label);
	exit(126);
	return (0);
}
