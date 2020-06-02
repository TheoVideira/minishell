/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 16:07:17 by user42            #+#    #+#             */
/*   Updated: 2020/06/02 23:11:39 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	if ((path = (char *)ft_dictget(g_mini.env, "PATH")) == 0)
		return (0);
	if (!(entries = ft_split(path, ':')))
		return (ALLOC_ERROR);
	i = 0;
	while (entries[i])
	{
		if ((r = search_entry(entries[i], label, ex)) < 0)
			free_char_array(entries);
		if (r)
			return (r);
		i++;
	}
	free_char_array(entries);
	return (0);
}

static void	launch_file(t_cmd *cmd)
{
	struct stat tmp;

	if (stat(cmd->label, &tmp) == -1)
	{
		ft_perror("minishell", cmd->label, 0);
		exit(127);
	}
	if (S_ISDIR(tmp.st_mode))
	{
		errno = EISDIR;
		ft_perror("minishell", cmd->label, 0);
		exit(126);
	}
	if ((tmp.st_mode & S_IEXEC) == 0)
	{
		errno = EACCES;
		ft_perror("minishell", cmd->label, 0);
		exit(126);
	}
	execve(cmd->label, cmd->args, g_mini.envtmp);
	ft_perror("minishell", cmd->label, 0);
	exit(1);
}

int			run_command(t_cmd *cmd)
{
	char	*path;
	int		r;
	int		fd;

	if ((fd = handle_redirs(cmd->redir)) == -1)
		exit(errno);
	if ((r = execute_builtin(cmd)) > -1)
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
	ft_perror("minishell", path, 0);
	exit(126);
	return (0);
}
